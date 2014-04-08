#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

# ifndef TYPE
# define TYPE int
# endif

struct DynArr
{
    TYPE *data;
    /* pointer to the data array */
    int size;
    /* Number of elements in the array */
    int capacity;
    /* capacity ofthe array */
};

void initDynArr(struct DynArr *v, int capacity)
{
    v->data = malloc(sizeof(TYPE) * capacity);
    assert(v->data != 0);
    v->size = 0;
    v->capacity = capacity;
    memset(v->data, 0, capacity * sizeof(TYPE) );
}

void freeDynArr(struct DynArr *v)
{
    if(v->data != 0)
    {
        free(v->data);
    /* free the space on the heap */
        v->data = 0;
    /* make it point to null */
    }
    v->size = 0;
    v->capacity = 0;
}

int sizeDynArr( struct DynArr *v)
{
    return v->size;
}

void _setCapacityDynArr(struct DynArr *v, int newCap){
    // declare temp array and initalize
    TYPE *tempArr = malloc(sizeof(TYPE)*newCap);

    //copy the elements of v into temp
    int i;
    for(i = 0; i < v->size; ++i){
        tempArr[i] = v->data[i];
    }

    // free old array
    free(v->data);
    assert(v != 0);

    //set v to address of temp
    v->data = tempArr;
    v->capacity = newCap;
}

TYPE getDynArr(struct DynArr *v, int position){
    assert(position > v->size);
    return v->data[position];
}

void addDynArr(struct DynArr *v, TYPE val)
{
    /* Check to see if a resize is necessary */
    if(v->size >= v->capacity){
        _setCapacityDynArr(v, 2 * v->capacity);
    }
    v->data[v->size] = val;
    v->size++;
}

void removeAtDynArr(struct DynArr *v, int val){
    TYPE *tempArr = malloc(sizeof(TYPE)*v->capacity);

    // copy value to temp array up to the value to be removed
    int i;
    for(i = 0; i < val; ++i){
        tempArr[i] = v->data[i];
    }
    // copy values above the one to be removed
    int j;
    for(j = val+1; j < v->size; ++j){
        tempArr[j-1] = v->data[j];
    }

    // free the old array
    free(v->data);

    // swap the arrays
    v->data = tempArr;

    v->size -= 1;

}

void putDynArr(struct DynArr *v, int position, TYPE val){
    assert(v->capacity > position);

    // temp array
    TYPE temp = v->data[position];

    if(v->size >= v->capacity){
        _setCapacityDynArr(v, 2 * v->capacity);
    }

    //move value above position up one spot
    int i;
    for(i = v->size; i > position; --i){
        v->data[i] = v->data[i-1];
    }

    v->data[position+1] = temp;
    v->data[position] = val;
}

void swapDynArr(struct DynArr *v, int p1, int p2){
    assert(v->capacity > p1 || v->capacity > p2);
    TYPE temp = v->data[p2];
    v->data[p2] = v->data[p1];
    v->data[p1] = temp;
}

void pushDynArr(struct DynArr *v, TYPE val){
    addDynArr(v, val);
}

void printDynArr(struct DynArr *v){
    int i;
    for(i = 0; i < v->size; ++i){
        printf("[%d]: %d\n", i, v->data[i]);
    }
}

TYPE topDynArr(struct DynArr *v){
    return v->data[v->size-1];
}

void popDynArr(struct DynArr *v){
    removeAtDynArr(v, v->size - 1);
}

int isEmptyDynArr(struct DynArr *v){
    if(v->size == 0){
        return 1;
    }
    return 0;
}
int main(){

    struct DynArr data;

    initDynArr(&data, 1);

    pushDynArr(&data, 10);

    printDynArr(&data);

    printf("Top: %d\n", topDynArr(&data));

    popDynArr(&data);

    printf("Empty?: %d\n", isEmptyDynArr(&data));

    freeDynArr(&data);
}

/* Questions:
1. What is the algorithmic execution time for the operations pop and top?
    both are O(1)

2. What is the algorithmic execution time for the operation push, assuming there is sufficient capacity for the new elements?
    also O(1) if there is no reallocation of the array

3. What is the algorithmic execution time for the internal method _setCapacityDynArr?
    The time for setCapacity is o(n)

4. Using as a basis your answer to 3, what is the algorithmic execution time for the operation push assuming that a new array must be created
    O(n)


