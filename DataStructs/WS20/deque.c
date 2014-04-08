#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


# ifndef TYPE
# define TYPE int
# endif

struct deque{
    TYPE *data;
    int capacity;
    int size;
    int beg;
};

void _dequeSetCapacity(struct deque *v, int newCap) {
    int i;
    /* Create a new underlying array*/
    TYPE *newData = (TYPE*)malloc(sizeof(TYPE)*newCap);
    assert(newData != 0);
    /* copy elements to it */
    int j =v->beg;
    for(i = 0; i <v->size; i++){
        newData[i] = v->data[j];
        j = j + 1;
        if(j >= v->capacity)
            j = 0;
    }

    /* Delete the oldunderlying array*/
    free(v->data);
    /* update capacity and size and data*/
    v->data = newData;
    v->capacity = newCap;
    v->beg = 0;
}

void dequeFree (struct deque *d) {
    free(d->data);
    d->size = 0;
    d->capacity = 0;
}

void dequeInit (struct deque *d, int initCapacity) {
    d->size = d->beg= 0;
    d->capacity = initCapacity;
    assert(initCapacity > 0);
    d->data = (TYPE*) malloc(initCapacity * sizeof(TYPE));
    assert(d->data != 0);
}

int dequeSize (struct deque *d) { return d->size; }

void _dequeDoubleCapacity (struct deque *d);

void dequeAddFront(struct deque *d,TYPE newValue) {
    if (d->size >= d->capacity) _dequeSetCapacity(d, 2*d->capacity);

    if(d->beg <= 0){
        d->beg = (d->capacity - 1);
    }
    else{
        d->beg = (d->beg - 1);
    }

    d->data[d->beg] = newValue;
    d->size++;
}

void dequeAddBack(struct deque *d,TYPE newValue) {
    if(d->size >= d->capacity) _dequeSetCapacity(d, 2*d->capacity);

    int index = d->beg + d->size;

    if(index >= d->capacity){
        index -= d->capacity;
    }

    d->data[index] = newValue;
    d->size++;
}



void print(struct deque *d){
    int i;
    for(i = 0; i < d->size; ++i){
        printf("%d: %d\n", i, d->data[d->beg+i]);
    }
}

TYPE dequeFront(struct deque *d){
    return d->data[d->beg];
}

TYPE dequeBack(struct deque *d){
    int index = d->beg + d->size - 1;

    if(index >= d->capacity){
        index -= d->capacity;
    }

    return d->data[index];
}

void dequeRemoveFront(struct deque *d){
    if(d->beg >= d->capacity - 1){
        d->beg = 0;
    }
    else{
        d->beg++;
    }
    d->size--;
}

void dequeRemoveBack(struct deque *d){
    assert(d->size > 0);
    d->size--;
}

int main(){

    struct deque *que;

    dequeInit(&que, 2);

    dequeAddFront(&que,10);
    dequeAddFront(&que,11);
    dequeAddFront(&que,8);
    dequeAddFront(&que,1);
        printf("back: %d\n", dequeBack(&que));
    printf("front: %d\n", dequeFront(&que));

    dequeAddBack(&que, 15);

    print(&que);

    dequeAddBack(&que, 5);
    dequeRemoveFront(&que);
    print(&que);
    printf("back: %d\n", dequeBack(&que));
    printf("front: %d\n", dequeFront(&que));
    dequeRemoveBack(&que);
    print(&que);
        printf("back: %d\n", dequeBack(&que));
    printf("front: %d\n", dequeFront(&que));
    dequeRemoveFront(&que);

            printf("back: %d\n", dequeBack(&que));
    printf("front: %d\n", dequeFront(&que));

return 0;
}
