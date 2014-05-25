/******************************************************
** Author: Jason Dorweiler
** Date: 10-28-13
** Description: CS165 Assignment 5
** Input:
** Output:


*******************************************************/
#include <iostream>
#include <cstdlib>
#include <string>

// struct to keep track of the greatest product for each type
struct greatest_prod{
    char type;
   // string position;
    int product;
    int row;
    int col;
};

void create_random_grid(int **&grid, int rows, int cols);
void print_grid(int **grid, int rows, int cols);
void search_grid(int **grid, greatest_prod *product, int rows, int cols);
void search_I(int **grid, greatest_prod *product, int rows, int cols);
void search_J(int **grid, greatest_prod *product, int rows, int cols);
void search_L(int **grid, greatest_prod *product, int rows, int cols);
void search_O(int **grid, greatest_prod *product, int rows, int cols);
void search_S(int **grid, greatest_prod *product, int rows, int cols);
void search_T(int **grid, greatest_prod *product, int rows, int cols);
void search_Z(int **grid, greatest_prod *product, int rows, int cols);

using namespace std;

int main(int argc, char **argv) {
    // get height and width of the table
    int rows = atoi(argv[1]);
    int cols= atoi(argv[2]);

    // array for the grid
    int **grid;

    // structs to keep track of products. One struct for
    // each of the 7 tetrimones
    greatest_prod product[7];

    // create the grid and fill with random ints
    create_random_grid(grid, rows, cols);

    // search grid
    search_grid(grid, product, rows, cols);

    print_grid(grid, rows, cols);

    cout << product[0].product << endl;
}

void search_grid(int **grid, greatest_prod *product, int rows, int cols){
    /*
    Search the grid for the greatest product of the tetris tetrimino shapes
    http://en.wikipedia.org/wiki/Tetris#Colors_of_Tetriminos.
    */
    search_I(grid, product, rows, cols);
    search_J(grid, product, rows, cols);
    search_L(grid, product, rows, cols);
    search_O(grid, product, rows, cols);
    search_S(grid, product, rows, cols);
    search_T(grid, product, rows, cols);
    search_Z(grid, product, rows, cols);

}

void search_I(int **grid, greatest_prod *product, int rows, int cols){
    // set product to zero in struct
    product[0].product = 0;

    long temp_product = 0;
    // search for vertical I-tetriminos
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows - 4; j++){
            temp_product = *grid[i];
            if(temp_product > product[0].product){
                product[0].product = temp_product;
                product[0].type = 'L';
                product[0].row = j;
                product[0].col = i;
            }
        }
    }

}

void search_J(int **grid, greatest_prod *product, int rows, int cols){

}

void search_L(int **grid, greatest_prod *product, int rows, int cols){

}

void search_O(int **grid, greatest_prod *product, int rows, int cols){

}

void search_S(int **grid, greatest_prod *product, int rows, int cols){

}

void search_T(int **grid, greatest_prod *product, int rows, int cols){

}

void search_Z(int **grid, greatest_prod *product, int rows, int cols){

}
void create_random_grid(int **&grid, int rows, int cols){
    // create array of ints
    grid = new int*[rows];

    // create array of array of ints and set to random int from 0-99
    for( int i = 0; i < cols; i++ ){
        grid[i] = new int[cols];
    }

    // fill the grid with random ints
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            grid[i][j] = rand() % 100;
        }
    }
}

void print_grid(int **arr, int rows, int cols){
    for(int i = 0; i < rows; i++){
        cout << "row #" << i << "  [";
        for(int j = 0; j < cols; j++){
            cout << arr[i][j];
            if(j % cols != cols -1 ){
                cout << " , ";
            }
        }
        cout << "]" << endl;
    }

}
