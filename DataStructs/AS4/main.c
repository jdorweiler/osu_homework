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

	myData1->number = 50;
	myData1->name = "rooty";
	myData2->number = 13;
	myData2->name = "lefty";
	myData3->number = 110;
	myData3->name = "righty";
	myData4->number = 10;
	myData4->name = "lefty of lefty";
    myData5->name = "right of lefty";
    myData5->number = 14;
    myData6->number = 115;
	myData6->name = "right right";
	myData7->number = 100;
	myData7->name = "right left";
    myData8->number = 114;
	myData8->name = "right right left";

	/*add the values to BST*/
	addBSTree(tree, myData1);
	addBSTree(tree, myData2);
	addBSTree(tree, myData3);
	addBSTree(tree, myData4);
	addBSTree(tree, myData5);
    addBSTree(tree, myData6);
	addBSTree(tree, myData7);
    addBSTree(tree, myData8);

    struct Node *current = tree->root;
    while(current != NULL){
        print_type(current->val);
        current = current->right;
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
void testAddNode() {
    struct BSTree *tree	= newBSTree();

    struct data myData1;
	struct data myData2;
	struct data myData3;
	struct data myData4;

	myData1.number = 50;
	myData1.name = "rooty";
    addBSTree(tree, &myData1);
    //check the root node
    if (compare(tree->root->val, (TYPE *) &myData1) != 0) {
        printf("addNode() test: FAIL to insert 50 as root\n");
        return;
    }
	//check the tree->cnt value after adding a node to the tree
    else if (tree->cnt != 1) {
        printf("addNode() test: FAIL to increase count when inserting 50 as root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 50 as root\n");


	myData2.number = 13;
	myData2.name = "lefty";
    addBSTree(tree, &myData2);

    //check the position of the second element that is added to the BST tree
    if (compare(tree->root->left->val, (TYPE *) &myData2) != 0) {
        printf("addNode() test: FAIL to insert 13 as left child of root\n");
        return;
    }
    else if (tree->cnt != 2) {
        printf("addNode() test: FAIL to increase count when inserting 13 as left of root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 13 as left of root\n");


	myData3.number = 110;
	myData3.name = "righty";
    addBSTree(tree, &myData3);

    //check the position of the third element that is added to the BST tree
    if (compare(tree->root->right->val, (TYPE *) &myData3) != 0) {
        printf("addNode() test: FAIL to insert 110 as right child of root\n");
        return;
    }
    else if (tree->cnt != 3) {
        printf("addNode() test: FAIL to increase count when inserting 110 as right of root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 110 as right of root\n");


	myData4.number = 10;
	myData4.name = "righty of lefty";
	addBSTree(tree, &myData4);

	//check the position of the fourth element that is added to the BST tree
    if (compare(tree->root->left->left->val, (TYPE *) &myData4) != 0) {
        printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
        return;
    }
    else if (tree->cnt != 4) {
        printf("addNode() test: FAIL to increase count when inserting 10 as left of left of root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 10 as left of left of root\n");
}

/*
fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree() {
    struct BSTree *tree = buildBSTTree();

    struct data myData1;
	struct data myData2;
	struct data myData3;
	struct data myData4;
	struct data myData5;

	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    myData5.number = 111;
	myData5.name = "not in tree";

    printTestResult(containsBSTree(tree, &myData1), "containsBSTree", "when test containing 50 as root");

    printTestResult(containsBSTree(tree, &myData2), "containsBSTree", "when test containing 13 as left of root");

	printTestResult(containsBSTree(tree, &myData3), "containsBSTree", "when test containing 110 as right of root");

    printTestResult(containsBSTree(tree, &myData4), "containsBSTree", "when test containing 10 as left of left of root");

     //check containsBSTree fucntion when the tree does not contain a node
    printTestResult(containsBSTree(tree, &myData5), "containsBSTree", "when test containing 111, which is  in the tree");

}

/*
fucntion to test the left_Most_element

*/
void testLeftMost() {
    struct BSTree *tree = buildBSTTree();

	struct data myData3;
	struct data myData4;

	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";

	printTestResult(compare(_leftMost(tree->root), &myData4) == 0, "_leftMost", "left most of root");

	printTestResult(compare(_leftMost(tree->root->left), &myData4) == 0, "_leftMost", "left most of left of root");

	printTestResult(compare(_leftMost(tree->root->left->left), &myData4) == 0, "_leftMost", "left most of left of left of root");

}

void testRemoveLeftMost() {
    struct BSTree *tree = buildBSTTree();
    struct Node *cur;

    //check that after removing the left most node of the tree
	cur = _removeLeftMost(tree->root);

	printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");

    cur = _removeLeftMost(tree->root->right);
    printTestResult(cur == tree->root->right, "_removeLeftMost", "removing leftmost of right of root 1st try");

 	cur = _removeLeftMost(tree->root);
    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
}

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
	myData7.number = 100;
	myData7.name = "right left";
    myData8.number = 114;
	myData8.name = "right right left";

    _removeNode(tree->root, &myData5);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->right == NULL, "_removeNode", "remove left of left of root 1st try");
    _removeNode(tree->root, &myData4);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");

    _removeNode(tree->root, &myData3);
	 printTestResult(compare(tree->root->val, &myData1) == 0 && compare(tree->root->right->val, &myData8) == 0, "_removeNode", "remove right of root 2st try");
    printTestResult(compare(tree->root->val, &myData1) == 0 && compare(tree->root->right->left->val, &myData7) == 0, "_removeNode", "remove right of root 2st try");

    _removeNode(tree->root, &myData2);
	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove right of root 3st try");

    cur = _removeNode(tree->root, &myData8);
    printTestResult(cur == tree->root, "_removeNode", "removing 114");

    cur = _removeNode(tree->root, &myData1);
    printTestResult(compare(tree->root->val, &myData7) == 0, "_removeNode", "remove right of root 4st try");

}

/*
Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){

    testAddNode();
	printf("\n");
    testContainsBSTree();
	printf("\n");
    testLeftMost();
	printf("\n");
    testRemoveLeftMost();
	printf("\n");
    testRemoveNode();
    return 0;
	getch();

}



