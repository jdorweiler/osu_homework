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

#define BLOCK_SIZE

using namespace std;

// struct to keep track of the greatest product for each type
class tetrimonoe{
    public:
        void setType(char t){
            char type = t;
        }

        void setPosition(string S){
            string position = S;
        }

        void setProduct(int P){
            int product = P;
        }

        void setRow(int R){
            int rows = R;
        }

        void setColumn(int C){
            int cols = C;
        }

        void setShape(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
            int shape[4][4] = {};
            shape[x1][y1] = shape[x2][y2] = shape[x3][y3] = shape[x4][y4] = 1;
        }

        void getProduct(){
            return product;
        }

    protected:
        int product;
};



void create_random_grid(int **&grid, int rows, int cols);
void print_grid(int **grid, int rows, int cols);
void search_grid(int **grid, tetrimonoe *shape, int rows, int cols);
void set_struct(tetrimonoe &shape, int temp_product, string position, char type, int row, int col);
void print_result(tetrimonoe *product);
void delete_grid(int **grid, int rows);
int errorChecker(char **argv, int argc);
void get_input(int &rows, int &cols, char **argv);
void search(int **grid, tetrimonoe *shape, char type, int rows, int cols, int rotations, int blockWidth, int blockHeight);

int main(int argc, char **argv) {

    if (errorChecker(argv, argc)){
        return 1;
    }

    int rows, cols;

    get_input(rows, cols, argv);

    // array for the grid
    int **grid;


    // structs to keep track of shapes. One struct for
    // each of the 7 tetrimones and their rotations
    tetrimonoe shape[19];

    // create the grid and fill with random ints
    create_random_grid(grid, rows, cols);

    cout << endl;
    print_grid(grid, rows, cols);

    // search grid
    search_grid(grid, shape, rows, cols);

    print_result(shape);

    delete_grid(grid, rows);

return 0;
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
        temp_prod = shape[i].getProduct;
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

    /*
    Call the search function.  send it the struct for the shape that you want to
    check for. The initial (i,j) coordinates for the shape and the  number of
    rotations to check.
    */
    search(grid, shape, 'I', rows, cols, 1, 4, 0 );

}

void rotate_block(*block_array, rows, cols, b11, b12, b21, b22, b31, b32, b41, b42){
    /*
    Function takes in the block array and the size of the array.  It takes in
    the i, j coordinates for where a block should be located in the block_array.
    */
    transpose(block_array, row, col);
    swap(block, row, col);
}

void set_struct(tetrimonoe &shape, int temp_product, string position, char type, int row, int col){
    shape.product = temp_product;
    shape.position = position;
    shape.type = type;
    shape.row = row;
    shape.col = col;


}

void search_I(int **grid, tetrimonoe *shape, char type, int rows, int cols, int rotations, int blockHeight, int blockWidth){
    cout << "Searching for I tetriminos ..." << endl;

    int temp_product = 0;

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
