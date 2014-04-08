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