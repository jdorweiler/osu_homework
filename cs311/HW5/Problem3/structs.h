/* 
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 5
*/
# define MSG_SIZE 30
// for messages from parcer to sort
typedef struct message{
  long mtype;
  char msg[MSG_SIZE];
} mess_t;


// nodes in the binary tree in sort
typedef struct wordNode{
	long mtype;
  char word[100];
  int number;

    // twalk is annoying and wont let
  // you pass any other variables so the
  // hack is to add the message queue that
  // needs to be used later on for the combiner 
  int q_to_combiner;
  
} mess_c;

// message from sort to combiner
// for messages from parcer to sort
typedef struct message_to_combiner{
  long mtype;
  struct wordNode *word;
} mess_s;