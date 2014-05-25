/*
 File: bst.c
 Implementation of the binary search tree data structure.

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
	int height;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};
/*----------AVL functions ____________________________________________________*/
int _h(struct Node * current){
    if (current == 0)
        return -1;
    return current->height;
}
int bf(struct Node *current){
	return _h(current->right) - _h(current->left);
}
void setHeight (struct Node * current) {
    int lch = _h(current->left);
    int rch = _h(current->right);
    if (lch < rch) current->height = 1 + rch;
        else current->height = 1 +lch;
}

struct Node *_balance(struct Node *current){

	int cbf = bf(current);

	if(cbf < -1){
		if(bf(current->left) > 0) // double rotation
			current->left  = rotateLeft(current->left);
		return rotateRight(current); //single rotation
	} else if (cbf > 1){
		if(bf(current->right) < 0)
			current->right = rotateRight(current->right);
		return rotateLeft(current);
	}
	setHeight(current);
	return current;
}

struct Node * rotateLeft(struct Node *current){
    struct Node *newTop;
    newTop = current->right;
    current->right = newTop->left;
    newTop->left = current;
    setHeight(current);
    setHeight(newTop);
    return newTop;

}

struct Node * rotateRight(struct Node *current){
    struct Node *newTop;
    newTop = current->left;
    current->left = newTop->right;
    newTop->right = current;
    setHeight(current);
    setHeight(newTop);
    return newTop;
}
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
            newNode->height = 0;
            return newNode;
        }

        // val is less than current->value
        if(compare(val, cur->val) == -1)
            cur->left = _addNode(cur->left, val);

    // val is greater than current->value
    else if(compare(val, cur->val) == 1)
            cur->right = _addNode(cur->right, val);

return _balance(cur);
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
    struct Node *temp;

    assert(cur != 0);

    if(cur->left != 0){
        cur->left = _removeLeftMost(cur->left);
        return _balance(cur);
    }
    // continue down the left side

    temp = cur->right;
    free(cur);

    return temp;
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
            if(cur->right == 0){
                    free(cur);
                  return cur->left;
            }
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
      return _balance(cur);
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

void printTree(struct BSTree *tree){

}
