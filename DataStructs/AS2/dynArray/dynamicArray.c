/******************************************************
** Author: Jason Dorweiler
** Date: 1/23/14
** Description: CS261 Assignment 2
** Dynamic Array ADT
******************************************************/
#include <assert.h>
#include <stdlib.h>
#include "dynamicArray.h"

#ifndef EQ
#define EQ(a,b) (a == b)
#endif

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

struct dynArrayIterator {
   struct DynArr *da;
   int currentIndex;
};
/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.
*/
DynArr* createDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array.

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure.

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{
    // declare temp array and initalize
    TYPE *tempArr = malloc(sizeof(TYPE)*newCap);

    //copy the elements of v into temp
    int i;
    for(i = 0; i < v->size; ++i){
        tempArr[i] = v->data[i];
    }

    // free old array
    free(v->data);
    assert(v!= 0);

    //set v to address of temp
    v->data = tempArr;
    v->capacity = newCap;
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
    /* Check to see if a resize is necessary */
    if(v->size >= v->capacity){
        _dynArrSetCapacity(v, 2 * v->capacity);
    }
    v->data[v->size] = val;
    v->size++;
}

void dynArrayAddAt(struct DynArr * da, int index, TYPE val) {
    if(da->size >= da->capacity){
        _dynArrSetCapacity(da, 2*da->capacity);
    }
    int i;
    for(i=da->size-1; i>index-1; --i){
        da->data[i+1] = da->data[i];
    }

    da->data[index];
}
/*	Get an element from the dynamic array from a specified position

	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
    assert(pos >= 0 && pos < v->size);
    return v->data[pos];
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
    assert(pos >= 0 && pos < v->size);
    v->data[pos] = val;
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *da, int i, int  j)
{
    if(i != j){
        assert(i >= 0 && i < da->size);
        assert(j >= 0 && j < da->size);
        TYPE temp = getDynArr(da, i);
        putDynArr(da, i, getDynArr(da, j));
        putDynArr(da, j, temp);
    }
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *da, int index)
{
    assert(index >= 0 && index < da->size);
         for (int i = index; i < da->size - 1; ++i)
               da->data[i] = da->data[i + 1];
         da->size--;
}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *da)
{
    return sizeDynArr(da) == 0;
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
    addDynArr(v, val);
}

/*	Returns the element at the top of the stack

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
    assert(sizeDynArr(v) != 0);
    return getDynArr(v, sizeDynArr(v) - 1);
}

/* Removes the element on top of the stack

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *da)
{
      assert(sizeDynArr(da) != 0);
      removeAtDynArr(da, sizeDynArr(da) - 1);
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
    int i;
    for(i = 0; i < v->size; ++i){
        if(EQ(val, v->data[i])){
            return 1;
        }
    }
    return 0;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr (struct DynArr * dy, TYPE test) {
int i;
     for (i = 0; i < dy->size; i++) {
          if (EQ(test, dy->data[i])) { /* found it */
                 removeAtDynArr(dy, i);
                 return;
          }
       }
}

void dynArrayIteratorInit(struct DynArr *da, struct dynArrayIterator *itr) {
            printf("%d\n", itr->currentIndex);
        itr->currentIndex = 0;
        printf("%d\n", itr->currentIndex);
        itr->da = da;
}

int dynArrayIteratorHasNext(struct dynArrayIterator *itr){
        if(itr->currentIndex < itr->da->size){
            return 1;
        }
        return 0;
}

TYPE dynArrayIteratorNext(struct dynArrayIterator *itr) {
    TYPE temp = itr->da->data[itr->currentIndex];
    itr->currentIndex++;
    return temp;
}

void dynArrayIteratorRemove (struct dynArrayIterator *itr) {
        removeAtDynArr(itr->da, itr->currentIndex);
        itr->currentIndex--;
}

int dynArrayIndex(struct dynArrayIterator *itr){
    return itr->currentIndex;
}
