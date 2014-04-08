#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.

 when there are no more words in the input file this function will return NULL.

 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

/*
 Load the contents of file into hashmap ht
 */
void loadDictionary(FILE* file, struct hashMap* ht);
void findWords(struct hashMap *hashTable, char* word);

int main (int argc, const char * argv[]) {
  clock_t timer;
  struct hashMap* hashTable;
  int tableSize = 1000;
  timer = clock();
  hashTable = createMap(tableSize);

  FILE* dictionary;

  loadDictionary(dictionary,hashTable);
  timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);

  char* word = (char*)malloc(256*sizeof(char));
  int quit=0;
  while(!quit){
    printf("Enter a word: ");
    scanf("%s",word);

    if(containsKey(hashTable, word)){
        printf("No spelling errors found\n");
    }
    else{
        findWords(hashTable, word);
        }


    /* Don't remove this. It is used for grading*/
    if(strcmp(word,"quit")==0)
      quit=!quit;
  }
  free(word);

  return 0;
}
/*
Two methods for finding related words from a misspelled word.
1. swap two letter and see if they are in the table.  This
    handles situations like: teh ->the or theer -> there

2. replace each letter in the word with the lettest a-z and
    check if any of those are in the table.
*/
void findWords(struct hashMap *hashTable,char* word){
        printf("** Word Not Found See Suggestions Below ** \n");
        int i,j;
        char *temp, *t1;
        // case 1: swapping
        for (i = 0; word[i+1] != '\0'; i++){
                char* testWord = strdup(word);// make a new copy of the word each time
                temp = testWord[i];
                t1 = testWord[i+1];
                testWord[i] = t1;
                testWord[i+1] = temp;
                if(containsKey(hashTable, testWord)){
                    printf("-> %s \n", testWord);
                }
            }

        //case 2: iterate a-z on each letter
        for (i = 0; word[i] != '\0'; i++){
            char* testWord = strdup(word);// make a new copy of the word each time
            for(j = 97; j < 123; ++j){
                testWord[i] = j;
                if(containsKey(hashTable, testWord)){
                    printf("-> %s \n", testWord);
                }
            }
        }
        printf("\n");
}
void loadDictionary(FILE* file, struct hashMap* ht)
{
    char *mode = "r";
    char *word, key;
    file = fopen("dictionary.txt", mode);
    assert(file);
    while((word = getWord(file)) != NULL){
            if(word)
                insertMap(ht, word, 1);
    }
    fclose(file);
}

void printValue(ValueType v) {
	printf("Value:%d",(int *)v);
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 16;
	char character;

	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);

	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   (character == 39)) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}

	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}
