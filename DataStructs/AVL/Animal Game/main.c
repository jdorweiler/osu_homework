#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "structs.h"
#include "assert.h"
struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};

TYPE _leftMost(struct Node *cur);
struct Node *_removeLeftMost(struct Node *cur);
struct Node *_removeNode(struct Node *cur, TYPE val);

struct BSTree *buildTree(struct BSTree *tree) {
	/*Create value of the type of data that you want to store*/
	struct data *myData1 = (struct data *) malloc(sizeof(struct data));
	struct data *myData2 = (struct data *) malloc(sizeof(struct data));
	struct data *myData3 = (struct data *) malloc(sizeof(struct data));
	struct data *myData4 = (struct data *) malloc(sizeof(struct data));
    struct data *myData5 = (struct data *) malloc(sizeof(struct data));
    struct data *myData6 = (struct data *) malloc(sizeof(struct data));
    struct data *myData7 = (struct data *) malloc(sizeof(struct data));
    struct data *myData8 = (struct data *) malloc(sizeof(struct data));
    struct data *myData9 = (struct data *) malloc(sizeof(struct data));
    struct data *myData10 = (struct data *) malloc(sizeof(struct data));
    struct data *myData11 = (struct data *) malloc(sizeof(struct data));
    struct data *myData12 = (struct data *) malloc(sizeof(struct data));
    struct data *myData13 = (struct data *) malloc(sizeof(struct data));
    struct data *myData14 = (struct data *) malloc(sizeof(struct data));
    struct data *myData15 = (struct data *) malloc(sizeof(struct data));

	myData1->number = 1000;
	myData1->name = "Does it fly?";
	myData2->number = 1500;
	myData2->name = "Does it have feathers?";
	myData3->number = 750;
	myData3->name = "Does it have fur?";
	myData4->number = 375;
	myData4->name = "Does it swim?";
	myData5->number = 450;
    myData5->name = "Is it a fish?";
    myData6->number = 1750;
	myData6->name = "Is it a bird?";
	myData7->number = 1800;
	myData7->name = "Yay, your animal is a bird!";
    myData8->number = 1400;
	myData8->name = "Is it a flying squirrel?";
    myData9->number = 451;
    myData9->name = "Yay, your animal is a fish";
    myData10->number = 850;
    myData10->name = "Does it have a tail?";
    myData11->number = 950;
    myData11->name = "Is it some kind of cat or dog?";
    myData12->number = 951;
    myData12->name = "Yay, your animal is a cat or dog!";
    myData13->number = 800;
    myData13->name = "Is your animal a bear?";
    myData14->number = 825;
    myData14->name = "Yay, your animal is a bear!";
    myData15->number = 1401;
	myData15->name = "Yay, its a flying squirrel!";



	/*add the values to BST*/
	addBSTree(tree, myData1);
	addBSTree(tree, myData2);
	addBSTree(tree, myData3);
	addBSTree(tree, myData4);
	addBSTree(tree, myData5);
    addBSTree(tree, myData6);
	addBSTree(tree, myData7);
    addBSTree(tree, myData8);
    addBSTree(tree, myData9);
    addBSTree(tree, myData10);
    addBSTree(tree, myData11);
    addBSTree(tree, myData12);
    addBSTree(tree, myData13);
    addBSTree(tree, myData14);
    addBSTree(tree, myData15);

    return tree;
}

void playGame(struct BSTree *tree){
    struct Node *current = tree->root;
    int userAns;
    while(current != NULL){
        printf(">>");
        print_type(current->val);
        printf("[0] NO [1] Yes: ");
        scanf("%d", &userAns);
        printf("\n");

        if(userAns == 0)
            current = current->left;
        else
            current = current->right;
    }
    if(userAns == 0){
        printf("Sorry I can't guess this animal\n");
    }
}

int main(int argc, char *argv[]){
    struct BSTree *tree	= newBSTree();
    buildTree(tree);
    playGame(tree);
    return 0;
}
