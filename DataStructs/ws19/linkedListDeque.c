#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

# ifndef TYPE
# define TYPE int
# endif

struct dlink{
    TYPE value;
    struct dlink *next;
    struct dlink *prev;
};

struct linkedList{
    int size;
    struct dlink *frontSentinel;
    struct dlink *backSentinel;
};

void linkedListInit(struct linkedList *q){
    q->frontSentinel = malloc(sizeof(struct dlink));
    assert(q->frontSentinel != 0);
    q->backSentinel = malloc(sizeof(struct dlink));
    assert(q->backSentinel != 0);
    q->frontSentinel->next = q->backSentinel;
    q->backSentinel->prev = q->frontSentinel;
    q->backSentinel->next = 0;
    q->size = 0;
}

void linkedListFree(struct linkedList *q){
    while(q->size > 0){
        linkedListRemoveFront(q);
    }
    free(q->frontSentinel);
    free(q->backSentinel);
    q->frontSentinel = q->backSentinel = NULL;
}

void linkedListAddFront(struct linkedList *q, TYPE e){
    _addBefore(q, q->frontSentinel->next, e);
}

void linkedListAddBack(struct linkedList *q, TYPE e){
    _addBefore(q, q->backSentinel, e);
}

void linkedListRemoveFront(struct linkedList *q){
    assert(!linkedListIsEmpty(q));
    _removeLink(q, q->frontSentinel->next);
}

void linkedListRemoveBack(struct linkedList *q){
    assert(!linkedListIsEmpty(q));
    _removeLink(q, q->backSentinel->prev);
}

int linkedListIsEmpty(struct linkedList *q){
    return q->size == 0;
}

void _addBefore(struct linkedList *q, struct dlink *link, TYPE e){
    struct dlink *temp = (struct dlink *)malloc(sizeof(struct dlink));
    assert(temp != 0);
    temp->value = e;
    temp->next = link;
    temp->prev = link->prev;
    link->prev->next = temp;
    link->prev = temp;
    q->size++;
}

void _removeLink(struct linkedList *q, struct dlink *link){
    link->prev->next = link->next;
    link->next->prev = link->prev;
    free(lnk);
    q->size--;
}

TYPE linkedListFront(struct linkedList *q){
    assert(!linkedListIsEmpty(q));
    return q->frontSentinel->next->value;
}

TYPE linkedListBack(struct linkedList *q){
       assert(!linkedListIsEmpty(q));
    return q->backSentinel->prev->value;
}

void print(struct linkedList *lst){
    struct dlink *link = lst->frontSentinel->next;
	while(link->next != 0){
        printf("%d\n", link->value);
        link = link->next;
	}
}

int main(){

    struct linkedList *deque;
    linkedListInit(&deque);


    linkedListAddFront(&deque, 1);
    linkedListAddFront(&deque, 2);
    linkedListAddFront(&deque, 3);


    printf("front: %d\n", linkedListFront(&deque));
    printf("back: %d\n", linkedListBack(&deque));

    linkedListAddBack(&deque, 8);
    linkedListAddBack(&deque, 7);
    linkedListAddBack(&deque, 6);

    printf("front: %d\n", linkedListFront(&deque));
    printf("back: %d\n", linkedListBack(&deque));

    linkedListRemoveBack(&deque);

    printf("front: %d\n", linkedListFront(&deque));
    printf("back: %d\n", linkedListBack(&deque));

    print(&deque);

return 0;
}
