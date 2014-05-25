#include <stdio.h>
#include <iostream>

struct node{
	int value;
	struct node *next;
	struct node *prev;
};

struct linkedList{
	struct node *front;
};

void initList(struct linkedList *lst){
	lst->front = new node;
	lst->front->value = 0;
	lst->front->next = 0;

}

void addlinkfront(struct linkedList *lst, int val){
    struct node *temp = new node;
    temp->value = val;
    if(lst->front->next != 0)
        lst->front->next->prev = temp;
    lst->front->next = temp;
}

int gettop(struct linkedList *lst){
    return lst->front->next->value;
}
int main(){

	struct linkedList *list;
	initList(list);

    addlinkfront(list, 10);

    std::cout << gettop(list);

return 0;
}
