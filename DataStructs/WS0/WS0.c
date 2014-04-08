#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

# ifndef ArrayBagStack
# define ArrayBagStack

# define TYPE int
# define EQ(a, b) (a == b)

struct arrayBagStack
{
    TYPE data [100];
    int count;
};

void initArray(struct arrayBagStack * b){
    b = (malloc(sizeof(TYPE)));
    assert(b->data != 0);
    b->count = 0;
}

void addArray(struct arrayBagStack * b, TYPE v){
    if(b->count < sizeof(b->data)){
        b->data[b->count] = v;
        b->count += 1;
    }
}

int containsArray(struct arrayBagStack * b, TYPE v){
    int i = 0;
    for(i; i < b->count; ++i){
        if(b->data[i] == v){
            return 1;
        }
    }
    return 0;
}

void removeArray(struct arrayBagStack * b, TYPE v){
    int i = 0;
    for(i; i < b->count; ++i){
        if(b->data[i] == v){
            b->data[i] = 0;
            b->count -= 1;
        }
    }
}

int sizeArray(struct arrayBagStack * b){
    return b->count;
}

void pushArray(struct arrayBagStack * b, TYPE v){
    //how is this different from addArray?
    addArray(b, v);
}

TYPE topArray(struct arrayBagStack * b){
    // last inserted element wihtout removing it
    return b->data[b->count-1];
}

void popArray(struct arrayBagStack * b){
    b->data[b->count] = 0;
    b->count -= 1;
}

int isEmptyArray(struct arrayBagStack * b){
    if(b->count > 0){
        return 0;
    }
    return 1;
}
# endif

int main(){
    struct arrayBagStack *data;

    initArray(data);

    addArray(data, 8);

    printf("size: %d\n", sizeArray((data)));

    printf("Empty: %d\n", isEmptyArray(data));

    printf("Contains 8: %d\n", containsArray(data, 8));

    printf("Top is: %d\n", topArray(data));

    printf("Contains 10: %d\n", containsArray(data, 10));

    pushArray(data, 12);

    printf("Top is: %d\n", topArray(data));

    printf("size: %d\n", sizeArray((data)));

    printf("Empty: %d\n", isEmptyArray(data));

    printf("Contains 8: %d\n", containsArray(data, 8));

    printf("Top is: %d\n", topArray(data));

    popArray(data);

    printf("Empty: %d\n", isEmptyArray(data));

    removeArray(data, 8);

    printf("Empty: %d\n", isEmptyArray(data));


    return 0;
}
