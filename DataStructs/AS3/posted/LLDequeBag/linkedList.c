/******************************************************
** Author: Jason Dorweiler
** Date: 1/30/14
** Description: CS261 Assignment 3
** Linked List Degue and bag
******************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

# ifndef TYPE
# define TYPE int
# endif

/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
    assert(lst != 0);
    lst->firstLink = malloc(sizeof(struct DLink));
    assert(lst->firstLink != 0);
    lst->lastLink = malloc(sizeof(struct DLink));
    assert(lst->lastLink != 0);
    lst->firstLink->next = lst->lastLink;
    lst->lastLink->prev = lst->firstLink;
    lst->lastLink->next = 0;
    lst->firstLink->prev = 0;
    lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_adDLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _adDLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
    assert(l != 0 && lst != 0);
    struct DLink *temp = (struct DLink *)malloc(sizeof(struct DLink));
    assert(temp != 0);
    temp->value = v;
    temp->next = l;
    temp->prev = l->prev;
    l->prev->next = temp;
    l->prev = temp;
    lst->size++;
}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
    assert(lst != 0);
    _adDLinkBefore(lst, lst->firstLink->next, e);
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
    assert(lst != 0);
    _adDLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
    assert(lst != 0 && lst->firstLink->next != 0);
    return lst->firstLink->next->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
    assert(lst != 0 && !isEmptyList(lst));
    return lst->lastLink->value;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
    assert(lst != 0 && l != 0);
    l->prev->next = l->next;
    l->next->prev = l->prev;
    lst->size--;
    free(l);
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
    assert(lst != 0 && !isEmptyList(lst));
    _removeLink(lst, lst->firstLink->next);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{
    assert(lst != 0 && !isEmptyList(lst));
    _removeLink(lst, lst->lastLink->prev);
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
    assert(lst != 0);
    return lst->size == 0;
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
    assert(lst != 0);
    struct DLink *link = lst->firstLink->next;
	while(link->next != 0){
        printf("%d\n", link->value);
        link = link->next;
	}
}

/*
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
    assert(lst != 0);
	addFrontList(lst, v);

}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
    assert(lst != 0 && !isEmptyList(lst));
    struct DLink *link = lst->firstLink->next;
	while(link->next != 0){
        if(link->value == e){
            return 1;
        }
        link = link->next;
	}
    return 0;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
    assert(!isEmptyList(lst) && lst != NULL);
    struct DLink *link = lst->firstLink->next;
	while(link != lst->lastLink){
        if(link->value == e){
            _removeLink(lst, link);
        }
        link = link->next;
	}
}

void deleteLinkedList(struct linkedList *lst){
    while(!isEmptyList(lst)){
        removeFrontList(lst);
    }
    free(lst->firstLink);
    free(lst->lastLink);
    free(lst);
}
