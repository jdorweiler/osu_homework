/*
 File: bst.c
 Animal game by Jason Dorweiler
 CS261 HW4
 Implementation of the binary search tree data structure
 and guess the animal game.   The game works by adding nodes
 to a binay search tree.  Left nodes for correct guesses
 and right nodes for wrong guesses.  If the user reaches a
 null node then they are asked to enter a question that will
 help determine what animal they were thinking of.  This question
 is added to the BST next time the game is played.

 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"


struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
 function to initialize the binary search tree.
 param tree
 pre: tree is not null
 post:	tree size is 0
		root is null
 */

void initBSTree(struct BSTree *tree)
{
	tree->cnt  = 0;
	tree->root = 0;
}

/*
 function to create a binary search tree.
 param: none
 pre: none
 post: tree->count = 0
		tree->root = 0;
 */

struct BSTree*  newBSTree()
{
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);

	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	if (node != 0) {
		_freeBST(node->left);
		_freeBST(node->right);
		free(node);
	}
}

/*
 function to clear the nodes of a binary search tree
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		tree->root = 0;
		tree->cnt = 0
 */
void clearBSTree(struct BSTree *tree)
{
	_freeBST(tree->root);
	tree->root = 0;
	tree->cnt  = 0;
}

/*
 function to deallocate a dynamically allocated binary search tree
 param: tree   the binary search tree
 pre: tree != null;
 post: all nodes and the tree structure itself are deallocated.
 */
void deleteBSTree(struct BSTree *tree)
{
	clearBSTree(tree);
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
 function to determine if  a binary search tree is empty.

 param: tree    the binary search tree
 pre:  tree is not null
 */
int isEmptyBSTree(struct BSTree *tree) { return (tree->cnt == 0); }

/*
 function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
 recursive helper function to add a node to the binary search tree.
 HINT: You have to use the compare() function to compare values.
 param:  cur	the current root node
		 val	the value to be added to the binary search tree
 pre:	val is not null
 */
struct Node *_addNode(struct Node *cur, TYPE val)
{
assert(val != NULL);
     struct Node *newNode;

        // we found the spot in the tree
        if(cur == NULL){
            newNode = malloc(sizeof(struct Node));
            assert(newNode != 0);
            newNode->val = val;
            newNode->left = newNode->right = 0;
            return newNode;
        }

        // val is less than current->value
        if(compare(val, cur->val) == -1)
            cur->left = _addNode(cur->left, val);

    // val is greater than current->value
    else if(compare(val, cur->val) == 1)
            cur->right = _addNode(cur->right, val);

return cur;
}

/*
 function to add a value to the binary search tree
 param: tree   the binary search tree
		val		the value to be added to the tree

 pre:	tree is not null
		val is not null
 pose:  tree size increased by 1
		tree now contains the value, val
 */
void addBSTree(struct BSTree *tree, TYPE val)
{
    assert(tree != NULL && val != NULL);
	tree->root = _addNode(tree->root, val);
	tree->cnt++;
}


/*
 function to determine if the binary search tree contains a particular element
 HINT: You have to use the compare() function to compare values.
 param:	tree	the binary search tree
		val		the value to search for in the tree
 pre:	tree is not null
		val is not null
 post:	none
 */

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
    assert(tree != NULL && val != NULL);
    struct Node *nodePtr = tree->root;
    do{
        int cmpVal = compare(nodePtr->val, val);
        // nodePtr is less than val
        if(cmpVal == -1)
            nodePtr = nodePtr->right;
        // nodePtr is greater than val
        else if(cmpVal == 1)
            nodePtr = nodePtr->left;
        // found the value!
        else if(cmpVal == 0)
            return 1;
    }while(nodePtr != NULL);
    return 0;
}

/*
 helper function to find the left most child of a node
 return the value of the left most child of cur
 param: cur		the current node
 pre:	cur is not null
 post: none
 */

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
	assert(cur != NULL);
    if(cur->left == NULL)
        return cur->val;
    cur = _leftMost(cur->left);
}


/*
 recursive helper function to remove the left most child of a node
 HINT: this function returns cur if its left child is NOT NULL. Otherwise,
 it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

 param: cur	the current node
 pre:	cur is not null
 post:	the left most node of cur is not in the tree
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
    assert(cur != NULL);

    if(cur->left == NULL){
        struct Node *temp = cur->right;
        _freeBST(cur);
        return temp;
    }
    // continue down the left side
    else
        cur->left = _removeLeftMost(cur->left);

    return cur;
}
/*
 recursive helper function to remove a node from the tree
 HINT: You have to use the compare() function to compare values.
 param:	cur	the current node
		val	the value to be removed from the tree
 pre:	val is in the tree
		cur is not null
		val is not null
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
    assert(cur != NULL && val != NULL);

    int cmpVal = compare(cur->val, val);

    //node value and test value are equal
      if(cmpVal == 0)
      {
            if(cur->right == NULL)
                  return cur->left;
            else
            {
                  cur->val = _leftMost(cur->right);
                  cur->right = _removeLeftMost(cur->right);
            }
      }
    //node value is greater than test value
      else if(cmpVal == 1)
            cur->left = _removeNode(cur->left, val);
      else
            cur->right = _removeNode(cur->right, val);
      return cur;
}
/*
 function to remove a value from the binary search tree
 param: tree   the binary search tree
		val		the value to be removed from the tree
 pre:	tree is not null
		val is not null
		val is in the tree
 pose:	tree size is reduced by 1
 */
void removeBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val)) {
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

struct BSTree *buildTree(struct BSTree *tree) {
    FILE *ifp;
    char *mode = "r";
    char name[201];
    int number;

    ifp = fopen("animalGame.txt", mode);

    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }

    while(fscanf(ifp, " %200[^,],%d", name, &number) == 2){

        /*Create value of the type of data that you want to store*/
        struct data *myData1 = malloc(sizeof(struct data));
        myData1->number = number;
        myData1->name = strdup(name);

        /*add the values to BST*/
        addBSTree(tree, myData1);
        }
        fclose(ifp);
        return tree;
}

void playGame(struct BSTree *tree){
    struct Node *current = tree->root;
    int userAns, curNode, prevNode;
    while(current != NULL){
        prevNode = curNode; // store previous nodes height
        curNode = getNumber(current->val);

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
        char newQuestion[200] = {'\0'};
        char newAnimal[200] = {'\0'};
        int newHeight = 0;  //height of new node

        if(prevNode > curNode)
            newHeight = curNode-(prevNode-curNode)/2;
        else
            newHeight = prevNode+(curNode-prevNode)/2;

        printf("Sorry I can't guess this animal\n\n");

        printf("Can you enter in a question to help me figure out your animal?\n");
        printf("enter your question here: ");
        getchar() != '\n'; // clear input buffer
        scanf("%199[^\n]", newQuestion);
        printf("What animal were you thinking of?: ");
        getchar() != '\n'; // clear input buffer
        scanf("%199[^\n]", newAnimal);
        // write new question to the file
        FILE *ofp;
        char *mode = "a";
        ofp = fopen("animalGame.txt", mode);
        fprintf(ofp, "%s,%d\n", &newQuestion, newHeight);
        fprintf(ofp, "Is it a %s?,%d\n", &newAnimal, newHeight+(curNode-newHeight)/2);
        fclose(ofp);

        printf("Your question and animal were added to the database, please play again\n\n");
        }

    if(userAns == 1){
        printf("Yay I guessed your animal!\n");
    }
}

void startScreen(){
    printf("*****  Guess the Animal Game **********\n");
    printf("Think of an animal and I will guess it\n");
    printf("***************************************\n\n");

}
int main(int argc, char *argv[]){
    struct BSTree *tree = newBSTree();
    startScreen();
    buildTree(tree);
    playGame(tree);
    return 0;
}
