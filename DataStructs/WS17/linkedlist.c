#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

# ifndef TYPE
# define TYPE int
# endif

struct link {
    TYPE value;
    struct link *next;
};

struct linkedListStack {
    struct link *firstLink;
};

void linkedListStackInit(struct linkedListStack *s){
    s->firstLink = 0;
}

void linkedListStackFree(struct linkedListStack *s){
    while(!linkedListStackIsEmpty(s)){
        linkedListStackPop(s);
    }
}

void linkedListStackPush(struct linkedListStack *s, TYPE d){
    struct link *newLink = (struct link *)malloc(sizeof(struct link));
    assert(newLink != 0);

    newLink->next = s->firstLink;
    s->firstLink= newLink;
    newLink->value = d;
}

TYPE linkedListStackTop(struct linkedListStack *s){
    assert(!linkedListStackIsEmpty(s));
    return s->firstLink->value;

}

void linkedListStackPop(struct linkedListStack *s){
    assert(!linkedListStackIsEmpty(s));
    struct link *temp = s->firstLink;
    s->firstLink = s->firstLink->next;
}

int linkedListStackIsEmpty(struct linkedListStack *s){
    return s->firstLink == 0;
}

int main(){

    struct linkedListStack *stack;
    linkedListStackInit(&stack);

    for(int i = 0; i < 10; ++i){
        linkedListStackPush(&stack, i+1);
    }

    for(int i = 0; i < 10; ++i){
        printf("top: %d\n", linkedListStackTop(&stack));
        linkedListStackPop(&stack);
    }

    printf("list is empty: %d\n", linkedListStackIsEmpty(&stack));

    linkedListStackPush(&stack, 1);
      printf("list is empty: %d\n", linkedListStackIsEmpty(&stack));
return 0;
}
