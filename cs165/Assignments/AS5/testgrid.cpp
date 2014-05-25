/******************************************************
** Author: Jason Dorweiler
** Date: 10-28-13
** Description: CS165 Assignment 5
** Input:
** Output:


*******************************************************/
#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

// struct to keep track of the greatest product for each type
struct tetrimonoe{
    char type;
    string position;
    int product;
    int row;
    int col;
    tetrimonoe(): product(0) {} // set initial product to zero for all tetrimonoes
};

void create_random_grid(int **&grid, int rows, int cols);
void print_grid(int **grid, int rows, int cols);
void search_grid(int **grid, tetrimonoe *shape, int rows, int cols);
void set_struct(tetrimonoe &shape, int temp_product, string position, char type, int row, int col);
void print_result(tetrimonoe *product);
void delete_grid(int **grid, int rows);
int errorChecker(char **argv, int argc);
void get_input(int &rows, int &cols, char **argv);
void search_I(int **grid, tetrimonoe *shape, int rows, int cols);
void search_J(int **grid, tetrimonoe *shape, int rows, int cols);
void search_L(int **grid, tetrimonoe *shape, int rows, int cols);
void search_O(int **grid, tetrimonoe *shape, int rows, int cols);
void search_S(int **grid, tetrimonoe *shape, int rows, int cols);
void search_T(int **grid, tetrimonoe *shape, int rows, int cols);
void search_Z(int **grid, tetrimonoe *shape, int rows, int cols);
void main_search(int **grid, tetrimonoe &shape, int rows, int cols, int rowVal, int colVal, string orientation, char type,  int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void print_test_matrix(int **grid, int rows, int cols);
int main(int argc, char **argv) {

    if (errorChecker(argv, argc)){
        return 1;
    }

    int rows, cols;

    get_input(rows, cols, argv);

    // array for the grid
    int grid[4][4] = {86,95,27,56,70,7,34,85,32,39,9,25,8,19,91,65};

    // structs to keep track of shapes. One struct for
    // each of the 7 tetrimones
    tetrimonoe shape[7];

    // create the grid and fill with random ints
 //   create_random_grid(grid, rows, cols);

    print_grid(grid, rows, cols);

    // search grid
    search_grid(grid, shape, rows, cols);

    print_result(shape);

    print_test_matrix(grid, rows, cols);

    delete_grid(grid, rows);

return 0;
}

void print_test_matrix(int **grid, int rows, int cols){
    cout << "{";
        for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
                cout << grid[i][j] << "," ;
            }
            }

cout << "}" << endl;
}


void get_input(int &rows, int &cols, char **argv){

    if(strcmp(argv[3], "-rows")){
        rows = atoi(argv[2]);
        cols = atoi(argv[4]);
    }

    if(strcmp(argv[1], "-rows")){
        rows = atoi(argv[4]);
        cols = atoi(argv[2]);
    }
 //   cout << rows << " " << cols << endl;
}

void print_result(tetrimonoe *shape){
    int temp_prod = 0;
    int result = 0;
    for(int i = 0; i < 8; i++){
        temp_prod = shape[i].product;
        if(temp_prod > shape[result].product){
            result = i;
        }
    }

cout<<"Max Prod: "<<shape[result].product<< " Row: "<<shape[result].row << " Col: "<< shape[result].col<<" Shape: "<< shape[result].type <<", "<<shape[result].position << endl <<endl;;
}

void search_grid(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search the grid for the greatest product of the tetris tetrimino shapes
    http://en.wikipedia.org/wiki/Tetris#Colors_of_Tetriminos
    */
    cout << "Starting Search " << endl;
    search_I(grid, shape, rows, cols);
    search_J(grid, shape, rows, cols);
    search_L(grid, shape, rows, cols);
    search_O(grid, shape, rows, cols);
    search_S(grid, shape, rows, cols);
    search_T(grid, shape, rows, cols);
    search_Z(grid, shape, rows, cols);

}

void set_struct(tetrimonoe &shape, int temp_product, string position, char type, int row, int col){
    shape.product = temp_product;
    shape.position = position;
    shape.type = type;
    shape.row = row;
    shape.col = col;
}

void main_search(int **grid, tetrimonoe &shape, int rows, int cols, int rowVal, int colVal, string orientation, char type,  int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    int temp_product = 0;
    for(int i = 0; i < rows-rowVal; i++){
        for(int j = 0; j < cols-colVal ; j++){
     //    cout << "The value of row: " << i << " column: " << j << " is " << grid[i][j] << endl;
            temp_product = grid[i+x1][j+y1]*grid[i+x2][j+y2]*grid[i+x3][j+y3]*grid[i+x4][j+y4];
          //  cout << "start " << grid[i][j] << " " << "product " << temp_product << endl;
            if(temp_product > shape.product){
                set_struct(shape, temp_product, orientation , type, i, j );
            }
        }
    }
}

void search_I(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for I tetriminos ..." << endl;

   main_search(grid, shape[0], rows, cols, 3, 0, "Vertical", 'I', 0, 0, 1, 0, 2, 0, 3, 0);

   main_search(grid, shape[0], rows, cols, 0, 3, "Horizontal", 'I', 0, 0, 0, 1, 0, 2, 0, 3);

}

void search_J(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for J tetriminos ..." << endl;
    main_search(grid, shape[4], rows, cols, 1, 2, "Horizontal Up", 'J', 0, 0, 1, 0, 1, 1, 1, 2);

    main_search(grid, shape[4], rows, cols, 1, 2, "Horizontal Down", 'J', 0, 0, 0, 1, 0, 2, 1, 2);

    main_search(grid, shape[4], rows, cols, 2, 1, "Vertical Up", 'J', 0, 1, 1, 1, 2, 1, 2, 0);

    main_search(grid, shape[4], rows, cols, 2, 1, "Vertical Down", 'J', 0, 0, 0, 1, 1, 0, 2, 0);

}

void search_L(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for L tetriminos ..." << endl;
    main_search(grid, shape[5], rows, cols, 1, 2, "Horizontal Up", 'L', 1, 0, 1, 1, 1, 2, 0, 2);

    main_search(grid, shape[5], rows, cols, 1, 2, "Horizontal Down", 'L', 1, 0, 0, 0, 0, 1, 0, 2);

    main_search(grid, shape[5], rows, cols, 2, 1, "Vertical Up", 'L', 0, 0, 1, 0, 2, 0, 2, 2);

    main_search(grid, shape[5], rows, cols, 2, 1, "Vertical Down", 'L', 0, 0, 0, 1, 1, 1, 2, 1);

}

void search_O(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for O tetriminos ..." << endl;
    main_search(grid, shape[1], rows, cols, 1, 1, "Square", 'O', 0, 0, 0, 1, 1, 0, 1, 1);

}

void search_S(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for S tetriminos ..." << endl;
    main_search(grid, shape[3], rows, cols, 1, 2, "Horizontal", 'S', 1, 0, 1, 1, 0, 1, 0, 2);

    main_search(grid, shape[3], rows, cols, 2, 1, "Vertical", 'S', 0, 0, 1, 0, 1, 1, 2, 1);

}

void search_T(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for T tetriminos ..." << endl;
    main_search(grid, shape[6], rows, cols, 1, 2, "Horizontal Up", 'T', 1, 0, 1, 1, 0, 1, 1, 2);

    main_search(grid, shape[6], rows, cols, 1, 2, "Horizontal Down", 'T', 0, 0, 0, 1, 1, 1, 0, 2);

    main_search(grid, shape[6], rows, cols, 2, 1, "Vertical Right", 'T', 0, 0, 1, 0, 1, 1, 2, 0);

    main_search(grid, shape[6], rows, cols, 2, 1, "Vertical Left", 'T', 1, 0, 1, 1, 0, 1, 2, 1);

}

void search_Z(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for Z tetriminos ..." << endl;
    main_search(grid, shape[2], rows, cols, 1, 2, "Horizontal", 'Z', 0, 0, 0, 1, 1, 1, 1, 2);

    main_search(grid, shape[2], rows, cols, 2, 1, "Vertical", 'Z', 0, 1, 1, 1, 1, 0, 2, 0);

    cout << endl;
}

void create_random_grid(int **&grid, int rows, int cols){
  //  cout << "Creating random " << rows << "x" << cols << " grid ..." << endl;
    // seed rand()
    srand(time(NULL));
    // create array of ints
    grid = new int*[rows];
   // cout << "Creating rows" << endl;
    // create array of array of ints and set to random int from 0-99
    for( int i = 0; i < rows; i++ ){
        grid[i] = new int[cols];
    }
 //   cout << "Creating columns" << endl;
    // fill the grid with random ints
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            grid[i][j] = rand() % 100;
      //      cout << "Creating entry " << i << " " << j << endl;
        }
    }
    cout << endl;
}

void print_grid(int **arr, int rows, int cols){

    for(int i = 0; i < rows; i++){
        cout << "row #" << i << "  [";
        for(int j = 0; j < cols; j++){
            if(arr[i][j] < 10){
                cout << "0" << arr[i][j];
            }
            else{
                cout << arr[i][j];
            }
            if(j % cols != cols -1 ){
                cout << " , ";
            }
        }
        cout << "]" << endl;
    }
cout << endl;
}

void delete_grid(int **grid, int rows){
    // delete the table by iterating through it and using delete
    //cout << "delete " << rows << " rows" <<endl;
        for(int i = 0; i < rows; i++){
         //   cout << "deleting row " << i << endl;
            delete grid[i];
        }
        delete [] grid;
}

int errorChecker(char **argv, int argc){
    if( argc < 3 || !(atoi(argv[2]) >= 4) || !(atoi(argv[4]) >= 4)){
        cout << "Correct usage is:  ./program [-rows <#rows>] [-cols <#columns>]" << endl;
        return 1;

    }
return 0;
}
