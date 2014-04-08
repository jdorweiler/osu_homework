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
    FILE *ifp;
    char *mode = "r";
    char *name;
    int number;

    ifp = fopen("animalGame.txt", mode);

    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }

    while(fscanf(ifp, "%100[^,], %d", name, &number) != EOF){
        printf("%s %d", name, number);
        /*Create value of the type of data that you want to store*/
        struct data *myData1 = (struct data *) malloc(sizeof(struct data));
        myData1->number = number;
        myData1->name = name;
        /*add the values to BST*/
        addBSTree(tree, myData1);
        }

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
