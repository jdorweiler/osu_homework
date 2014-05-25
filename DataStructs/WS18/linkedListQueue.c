#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

# ifndef TYPE
# define TYPE int
# endif

struct link{
    TYPE value;
    struct link *next;
};

struct listQueue{
    struct link *firstLink;
    struct link *lastLink;
};

void listQueueInit(struct listQueue *q){
    struct link *lnk = (struct link *)malloc(sizeof(struct link));
    assert(lnk != 0);
    lnk->next = 0;
    q->firstLink = q->lastLink = lnk;
}

void listQueueAddBack(struct listQueue *q, TYPE e){
    struct link *newLnk = (struct link *)malloc(sizeof(struct link));
    assert(newLnk != 0);
    newLnk->next = 0;
    newLnk->value = e;
    q->lastLink->next = newLnk;

}

TYPE listQueueFront(struct listQueue *q){
    assert(!listQueueIsEmpty(q));
    return q->firstLink->next->value;
}

void listQueueRemoveFront(struct listQueue *q){
    assert(!listQueueIsEmpty(q));
    struct link *tempLnk = q->firstLink->next;
    q->firstLink->next = tempLnk->next;
    free(tempLnk);
}

int listQueueIsEmpty(struct listQueue *q){
    return q->firstLink == q->lastLink;
}

int main(){

    struct listQueue *stack;
    listQueueInit(&stack);

    printf("empty: %d\n", listQueueIsEmpty(&stack));
    listQueueAddBack(&stack,1);
    listQueueAddBack(&stack,2);
    listQueueAddBack(&stack,3);

    printf("empty: %d\n", listQueueIsEmpty(&stack));
    printf("%g\n", listQueueFront(&stack));

    printf("empty: %d\n", listQueueIsEmpty(&stack));


return 0;
}
