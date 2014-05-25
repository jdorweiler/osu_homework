#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

# ifndef TYPE
# define TYPE int
# endif

//global to keep track of total additions
int count = 0;

// global for units of time before each reassignment
int segmentTime = 0;


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

    // Zero the data array before using it.
    // this seems like a good idea??
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
    segmentTime = (segmentTime*v->size);
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

    // one unit of time for assignment of the new array
    segmentTime++;

    v->capacity = newCap;
}

void addDynArr(struct DynArr *v, TYPE val)
{

    /* Check to see if a resize is necessary */
    if(v->size >= v->capacity){
        printf("Segment Time: %d Values added: %d Array Size: %d Average: %f\n",
               segmentTime, count, v->size, (float)segmentTime/(float)count);
        count = 0;
        segmentTime = 1;
        _setCapacityDynArr(v, 2 * v->capacity);
    }
    v->data[v->size] = val;
    v->size++;
    count += 1;
    segmentTime += 1;
}


int main(){

    struct DynArr data;

    initDynArr(&data, 5);

    for(int i = 0; i < 25; ++i){
        addDynArr(&data, i);
    }
    printf("Segment Time: %d Values added: %d Array Size: %d Average: %f\n",
               segmentTime, count, data.size, (float)segmentTime/(float)count);

    freeDynArr(&data);
}
