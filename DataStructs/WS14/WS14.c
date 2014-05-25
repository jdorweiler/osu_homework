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
    memset(v->data, 0, capacity * sizeof(TYPE));
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
    assert(v!= 0);

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

int main(){

    struct DynArr data;

    initDynArr(&data, 1);

    printf("Size of array: %d\n", sizeDynArr(&data));
    printf("Capacity of array: %d\n", data.capacity);

    for(int i = 0; i < 14; ++i){
        addDynArr(&data, i);
    }


    printf("Size of array: %d\n", sizeDynArr(&data));
    printf("Capacity of array: %d\n", data.capacity);

    for(int i = 0; i < sizeDynArr(&data); ++i){
        printf("%d: %d\n", i, data.data[i]);
    }

    removeAtDynArr(&data, 3);

    printf("Size of array: %d\n", sizeDynArr(&data));
    printf("Capacity of array: %d\n", data.capacity);

    for(int i = 0; i < sizeDynArr(&data); ++i){
        printf("%d: %d\n", i, data.data[i]);
    }

    putDynArr(&data, 3, 56);

    printf("Size of array: %d\n", sizeDynArr(&data));
    printf("Capacity of array: %d\n", data.capacity);

    for(int i = 0; i < sizeDynArr(&data); ++i){
        printf("%d: %d\n", i, data.data[i]);
    }

    swapDynArr(&data, 3, 7);

    printf("Size of array: %d\n", sizeDynArr(&data));
    printf("Capacity of array: %d\n", data.capacity);

    for(int i = 0; i < sizeDynArr(&data); ++i){
        printf("%d: %d\n", i, data.data[i]);
    }

    freeDynArr(&data);
}
