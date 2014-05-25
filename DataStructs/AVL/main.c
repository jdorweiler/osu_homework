#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "structs.h"

/* Example main file to begin exercising your tree */

/*
Functions to test

struct Node *_addNode(struct Node *cur, TYPE val)
int containsBSTree(struct BSTree *tree, TYPE val)
TYPE _leftMost(struct Node *cur)
struct Node *_removeLeftMost(struct Node *cur)
struct Node *_removeNode(struct Node *cur, TYPE val)
*/


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

/*
function to built a Binary Search Tree (BST) by adding numbers in this specific order
the graph is empty to start: 50, 13, 110 , 10

*/
struct BSTree *buildBSTTree() {
    /*     50
         13  110
        10
    */
    struct BSTree *tree	= newBSTree();

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

	myData1->number = 50;
	myData1->name = "rooty";
	myData2->number = 13;
	myData2->name = "lefty";
	myData3->number = 11;
	myData3->name = "righty";
	myData4->number = 9;
	myData4->name = "lefty of lefty";
    myData5->name = "right of lefty";
    myData5->number = 14;
    myData6->number = 80;
	myData6->name = "right right";
	myData7->number = 85;
	myData7->name = "right left";
    myData8->number = 87;
	myData8->name = "right right left";
    myData9->number = 79;
	myData9->name = "right right left";

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

_removeNode(tree->root, myData2);

printf("printing node\n");
    struct Node *current = tree->root;
    while(current != 0){
        print_type(current->val);
        if(current->left != 0){
            print_type(current->left->val);
        }
        printf("next node\n");
        current = current->right;
    }
    printf("moving node\n");
   current = tree->root->right;
        while(current != 0){
        print_type(current->val);
        if(current->right != 0){
            print_type(current->right->val);
        }
        printf("next node\n");
        current = current->left;
    }
    return tree;
}

/*
function to print the result of a test function
param: predicate:  the result of the test
       nameTestFunction : the name of the function that has been tested
	   message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message){
	if (predicate)
	   printf("%s(): PASS %s\n",nameTestFunction, message);
    else
	   printf("%s(): FAIL %s\n",nameTestFunction, message);
}

/*
fucntion to test each node of the BST and their children

*/

void testRemoveNode() {
    struct BSTree *tree = buildBSTTree();
    struct Node *cur;
    struct data myData1;
	struct data myData2;
	struct data myData3;
	struct data myData4;
	struct data myData5;
    struct data myData6;
	struct data myData7;
    struct data myData8;

	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    myData5.number = 14;
	myData5.name = "righty of lefty";
    myData6.number = 115;
	myData6.name = "right right";
	myData7.number = 116;
	myData7.name = "right left";
    myData8.number = 117;
	myData8.name = "right right left";

//    _removeNode(tree->root, &myData5);
//    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->right == NULL, "_removeNode", "remove left of left of root 1st try");
//    _removeNode(tree->root, &myData4);
//    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");
//
//    _removeNode(tree->root, &myData3);
//	 printTestResult(compare(tree->root->val, &myData1) == 0 && compare(tree->root->right->val, &myData8) == 0, "_removeNode", "remove right of root 2st try");
//    printTestResult(compare(tree->root->val, &myData1) == 0 && compare(tree->root->right->left->val, &myData7) == 0, "_removeNode", "remove right of root 2st try");
//
//    _removeNode(tree->root, &myData2);
//	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove right of root 3st try");
//
//    cur = _removeNode(tree->root, &myData8);
//    printTestResult(cur == tree->root, "_removeNode", "removing 114");
//
//    cur = _removeNode(tree->root, &myData1);
//    printTestResult(compare(tree->root->val, &myData7) == 0, "_removeNode", "remove right of root 4st try");

}

/*
Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){


    testRemoveNode();
    return 0;
	getch();

}



