/* 
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 5

compile with Makefile, run time tests for 1,2,3,4,5,10,15,20
processes with : make time
*/
// source (1) for tsearch/twalk: 
// https://github.com/perusio/linux-programming-by-example/blob/master/book/ch14/ch14-tsearch.c


#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include "structs.h"
#include <search.h>
#include <stdlib.h>
#include <assert.h>

# define QUEUE_PERMS 0644

void create_parser( void );
void sort( int q_number, int sort_process_no );
int compare(const void *e1p, const void *e2p);
void create_combiner_queues(key_t *sortKeys);
void create_parser_queue( void );
void send_to_combiner(const void *nodep, const VISIT which, const int depth);
void combiner( void );
int get_message_number(int wordSum);
void sigHandler(void);

// these need to be global to clean up with SIGINT handler
static int message_queue = (int) 0;
static key_t key = (key_t) 0;
int *combiner_queues;
int num_sort;

void sigHandler( void ){
  int i;
  // clean up queues
    // remove combiner queues
  for(i = 0; i < num_sort; i++){
   msgctl(combiner_queues[i], IPC_RMID, NULL);
  }

  // remove parser queue
  msgctl(message_queue, IPC_RMID, NULL);

  exit(0);
}
/*
b-tree hash function.
map the first letter of the word to a binary tree message number
so that we have b-trees grouped in alphabetical order.
postorder traversal of the b-trees then gives correct sorted output
*/
int get_message_number(int wordSum){
  int total = 0;
  int returnval = 1;

  // we now have a number 0-26
  wordSum -= 97;
  
  // find the b-tree based on the number of processes 
  while(wordSum > total){
    total += 26/num_sort;
    returnval++;
  }
  
  // make sure it doesn't return a value greater than
  // the number of sort processes that we have.
  if(returnval > num_sort){
    returnval = num_sort;
  }
  return returnval;
}

/*
fork a parser process and tokenize from stdin
then send the individual words off to the
sort processes
*/
void create_parser( void ){

  const char delimiters[] = " +=_-\\,\'.-;:\"<>\t{}[]!?()=/|~`1234567890@#$%^&\r\n*\n";
  char *word = NULL;
  size_t buffer = 100;
  char *token;
  mess_t message;
  int i;
  int messageNo;
  int child;

  // create parser process. This tokenizes the strings
  // and send each work to the sort function(s)
  if((child = fork()) == 0){
      // child process # 1 starts here
      key = ftok(__FILE__,'x');
      message_queue = msgget(key, QUEUE_PERMS);

      // splitting the words up 
      while(getline(&word, &buffer, stdin) != EOF){
        token = strtok(word, delimiters);
        while(token != NULL){
          for(i = 0; token[i]; i++){
            token[i] = tolower(token[i]);
          }
            // get b-tree number for the message mtype
            messageNo = get_message_number(token[0]);
            if(messageNo > num_sort){
              messageNo--;
            }

          message.mtype = messageNo;
          // copy the word (token) over to the message struct
          strcpy(message.msg,token);
          if(msgsnd(message_queue, &message, MSG_SIZE, MSG_NOERROR) == -1){
          // perror("send failed 1");
          }
          token = strtok(NULL, delimiters);
        }
      }

      // send a message to all sort processes
      // that we are finished tokenizing
      for(i = 1; i < num_sort+1; i++){
        message.mtype = i;
        strcpy(message.msg, "tokenizer_finished");

        if(msgsnd(message_queue, &message, MSG_SIZE, MSG_NOERROR) == -1){
          perror("send failed end tokenizer");
        }
      }
      _exit(EXIT_SUCCESS);
  }
}

// modified from source (1)
// compare function for b-tree nodes
// it the two are identical then just 
// incriment the counter number for  that word
int compare(const void *e1p, const void *e2p){
  struct wordNode *e1, *e2;
  int retval;

  e1 = (struct wordNode *) e1p;
  e2 = (struct wordNode *) e2p;

  retval = strcmp(e1->word, e2->word);
    if(retval == 0) {
      e1->number += 1;
      e2->number += 1;
    }
  return retval;
}

// modified from source(1)
// postorder traversal of b-tree
// send data from the node to the combiner via message queue
void send_to_combiner(const void *nodep, const VISIT which, const int depth){

  struct wordNode *e = *((struct wordNode **) nodep);

  switch (which) {
    case leaf:
    case postorder:
     // printf("word: %s number: %d\n", e->word, e->number);
          e->mtype = 1;
          if(msgsnd(e->q_to_combiner, e, sizeof(struct wordNode), MSG_NOERROR) == -1){
            perror("send failed 2");
          }
      break;
    default:
    break;
    }
}

/*
fork a sort process and read in data from the
parser message queue.
*/
void sort(int q_number, int sort_process_no ){
  mess_t message2;
  struct wordNode *newWord;
  int combiner_queue_no;
  void *root = NULL;
  int child;

  if((child = fork()) == 0){

      // child process # 2 starts here
      // connect to processer queue
      key = ftok(__FILE__,'x');
      message_queue = msgget(key, QUEUE_PERMS );

      // connect to the numbered combiner queue
      combiner_queue_no = msgget(q_number, QUEUE_PERMS );

      // read from the parser queue waiting for a message with
      // sort_process_no
      while(msgrcv(message_queue, &message2, MSG_SIZE, sort_process_no, MSG_NOERROR) != -1 ){

        // see if we got the end message
        if(strcmp(message2.msg, "tokenizer_finished") == 0){
          break;
        }

        // allocate memory for word and set up message struct
        newWord = malloc(sizeof(struct wordNode));
        strcpy(newWord->word,message2.msg);
        newWord->number = 1;
        newWord->q_to_combiner = combiner_queue_no;

        // add to the binary tree
        tsearch(newWord, & root, compare);
      }  // end while

      // do an postorder traversal and send the data to the combiner
      twalk(root, send_to_combiner);

      // send end of sort message
      newWord = malloc(sizeof(struct wordNode));
      strcpy(newWord->word,"sort_finished");
      newWord->number = 1;
      newWord->q_to_combiner = combiner_queue_no;
      newWord->mtype = 1;

      if(msgsnd(combiner_queue_no, newWord, sizeof(struct wordNode), MSG_NOERROR)== -1){
        perror("end sort message failed: ");
      }
      _exit(EXIT_SUCCESS);
  }
}

void create_parser_queue( void ){
   // set up a message queue
  key = ftok(__FILE__,'x');
  // create queue
  message_queue = msgget(key, QUEUE_PERMS | IPC_CREAT);
    if(message_queue == -1){
    perror("creating message queue");
   }
}

void create_combiner_queues(key_t *sortKeys){

  // set up num_sort number of queues to connect
  // the individual sort processes to the combiner
  // num_sort is 1 - 50
  int i;
  for( i = 0; i < num_sort; i++){
    // create key
    sortKeys[i] = ftok(__FILE__,i);
    // create queue
    combiner_queues[i] = msgget(sortKeys[i], QUEUE_PERMS | IPC_CREAT);

   // printf("Created Combiner queue: %d\n", combiner_queues[i]);
  }
}

void combiner( void ){
  int i;
  struct wordNode *node;
  node = malloc(sizeof(struct wordNode));

  // starting with combiner queue 0 and up. print out their messages.
  // the trees are traversed in alphabetical order so the messages
  // just need to be read and printed out. 
  for(i = 0; i < num_sort; i++){
      while(msgrcv(combiner_queues[i], node, sizeof(struct wordNode), 1, MSG_NOERROR) != -1){
          if(strcmp(node->word, "sort_finished") == 0){
            break;
          }
          printf("%7d %s\n",node->number, node->word);
    }
  }
}

int main(int argc, char *argv[]){
  int i;
  char c;
  key_t *sortKeys;
  struct sigaction action;
  action.sa_handler = sigHandler;
  num_sort = 1;

  while ((c = getopt (argc, argv, "n:")) != -1)
  {
    switch (c)
    {
    case 'n':
      if(atoi(optarg) < 0 || atoi(optarg) > 50){
        printf("invalid No. of sort processes, defaulting to 1\n");
        num_sort = 1;
      }
      else{
        num_sort = atoi(optarg);
      }
      break;
    default:
      break;
    }
  }

  sigaction(SIGINT, &action, NULL);

  // create memory for key and queue arrays
  sortKeys = malloc(sizeof(key_t)*num_sort);
  assert(sortKeys);
  combiner_queues = malloc(sizeof(int)*num_sort);
  assert(combiner_queues);


  create_parser_queue( /* no args */);

  create_combiner_queues(sortKeys);

  // calling sort before the parser
  // seem to give better results.. i.e. it works
  for(i = 0; i < num_sort; i++){
    sort(sortKeys[i], i+1);
  }

  // create parser
  create_parser(/* no args */);

  // wait for the parser to finish
  wait(NULL);

  combiner(/* no args */);

  // wait for n - sort processes to finish
  for(i = 0; i < num_sort; i++){
    wait(NULL);
  }

  // remove combiner queues
  for(i = 0; i < num_sort; i++){
   msgctl(combiner_queues[i], IPC_RMID, NULL);
  }

  // remove parser queue
  msgctl(message_queue, IPC_RMID, NULL);

  exit(EXIT_SUCCESS);
}
