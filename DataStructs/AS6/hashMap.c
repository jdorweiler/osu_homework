#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

//struct hashLink {
//   KeyType key; /*the key is what you use to look up a hashLink*/
//   ValueType value; /*the value stored with the hashLink, a pointer to int in the case of concordance*/
//   struct hashLink * next; /*notice how these are like linked list nodes*/
//};
//typedef struct hashLink hashLink;
//
//struct hashMap {
//    hashLink ** table; /*array of pointers to hashLinks*/
//    int tableSize; /*number of buckets in the table*/
//    int count; /*number of hashLinks in the table*/
//};
//typedef struct hashMap hashMap;


//int stringHash2(char * str)
//{
//	int i;
//	int r = 0;
//	for (i = 0; str[i] != '\0'; i++)
//		r += str[i] << i;
//	return r;
//}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{
    int size = ht->tableSize;
    struct hashLink *cur, *prev;
    int i;
    for( i = 0; i < size; ++i){
        cur = ht->table[i];
        while(cur != 0){
            free(cur->key);
            prev = cur;
            cur = cur->next;
            free(prev);
        }
        free(cur);
    }
    free(ht->table);
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
    int oldSize = ht->tableSize;
    struct hashLink **oldTable = ht->table;
    _initMap(ht, oldSize*2);
    struct hashLink *cur, *prev;
    // copy table
    int i;
    for( i = 0; i < oldSize; ++i){
        cur = oldTable[i];
        while(cur != 0){
            insertMap(ht,cur->key, cur->value);
            prev = cur;
            cur = cur->next;
            free(prev);
        }
    }
    free(oldTable);
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
    int hashIndex = stringHash2(k)%ht->tableSize;

    if(hashIndex < 0)
        hashIndex += ht->tableSize;

    // see if link exists already
    if(ht->table[hashIndex]){
        hashLink *curLink = ht->table[hashIndex];
        while(curLink != NULL){
            if(strcmp(curLink->key,k) == 0){
                curLink->value++;
                return;
            }
            curLink = curLink->next;
        }
    }

    // key isn't in table yet so add a new one
        //check load factor
    struct hashLink *newLink = malloc(sizeof(hashLink));
    newLink->value = v;
    newLink->key = k;
    newLink->next = ht->table[hashIndex];
    ht->table[hashIndex] = newLink;
    ht->count++;

    if(ht->count/(double)ht->tableSize > LOAD_FACTOR_THRESHOLD)
        _setTableSize(ht, 2*ht->tableSize);
}


/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
      int idx = stringHash2(k) % ht->tableSize;
      if (idx < 0)
            idx += ht->tableSize;
      struct hashLink *cur = ht->table[idx];
      while (cur != 0)
      {
            if (strcmp(cur->key, k) == 0)
                  return (ValueType *)cur->value;
            cur = cur->next;
      }
      return NULL;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
      int idx = stringHash2(k) % ht->tableSize;
      if (idx < 0)
            idx += ht->tableSize;
      struct hashLink *cur = ht->table[idx];
      while (cur != 0)
      {
            if (strcmp(cur->key,k) == 0)
                  return 1;
            cur = cur->next;
      }
      return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType testElement)
{
    assert(ht->count > 0);
   // KeyType Element = strdup(testElement); //make a char* copy
    int idx = stringHash2(testElement) % ht->tableSize;
    if(containsKey(ht, testElement))
      {
        struct hashLink *cur = ht->table[idx];
        struct hashLink *prev = ht->table[idx];
        while (cur != 0)
        {
                if(strcmp(cur->key,testElement) == 0)
                {
                    if(cur == ht->table[idx]) /* element is first in list */
                        ht->table[idx] = cur->next;
                    else
                        prev->next = cur->next;
                    free(cur->key);
                    free(cur);
                    cur = 0; /* breaks out of while loop */
                }
                else
                {
                    prev = cur;
                    cur = cur->next;
                }
        }
    }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
	return ht->count;

}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
	int count, i;
	count = 0;
	for(i = 0; i < ht->tableSize; ++i){
        if(ht->table[i] == NULL)
            count++;
	}
	return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
	return ht->count/(double)ht->tableSize;
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		while(temp != 0){
			printf("%s ", temp->key);
			printValue(temp->value);

			temp=temp->next;
			if(temp == 0)
                printf("\n");
		}

	}
}


