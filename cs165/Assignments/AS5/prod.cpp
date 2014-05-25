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

int main(int argc, char **argv) {

    if (errorChecker(argv, argc)){
        return 1;
    }

    int rows, cols;

    get_input(rows, cols, argv);

    // array for the grid
    int **grid;

    // structs to keep track of shapes. One struct for
    // each of the 7 tetrimones
    tetrimonoe shape[7];

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

void main_search(int **grid, tetri)

void search_I(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for I tetriminos ..." << endl;

    int temp_product = 0;

    // search for vertical I-tetriminos
    for(int i = 0; i <= rows-4; i++){
      //  cout << "first loop" << endl;
        for(int j = 0; j < cols ; j++){
         //   cout << "The value of row: " << i << " column: " << j << " is " << grid[i][j] << endl;
            temp_product = grid[i][j]*grid[i+1][j]*grid[i+2][j]*grid[i+3][j];
          // cout << "start " << grid[i][j] << " " << "end " << grid[i+3][j]  << " Product "<< temp_product << endl;
            if(temp_product > shape[0].product){
                set_struct(shape[0], temp_product, "Vertical", 'I', i, j );
            }
        }
    }
    // search for horizontal I-tetriminos
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <= cols-4 ; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i][j+2]*grid[i][j+3];
          //  cout << "start " << grid[i][j] << " " << "end " << grid[i][j+3]  << " Product "<< temp_product  << " stored product " << shape[0].product << endl;
            if(temp_product > shape[0].product){
                set_struct(shape[0], temp_product, "Horizontal", 'I', i, j );
            }
        }
    }



}

void search_J(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for J tetriminos ..." << endl;

    // temp product is zero
    int temp_product = 0;

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i][j]*grid[i+1][j]*grid[i+1][j+1]*grid[i+1][j+2];
            if(temp_product > shape[4].product){
                set_struct(shape[4], temp_product, "Horizontal-Up", 'J', i, j );
            }
        }
    }

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i][j+2]*grid[i+1][j+2];
            if(temp_product > shape[4].product){
                set_struct(shape[4], temp_product, "Horizontal-Down", 'J', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j+1]*grid[i+1][j+1]*grid[i+2][j+1]*grid[i+2][j];
            if(temp_product > shape[4].product){
                set_struct(shape[4], temp_product, "Vertical-Left", 'J', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i+1][j]*grid[i+2][j];
            if(temp_product > shape[4].product){
                set_struct(shape[4], temp_product, "Vertical-Right", 'J', i, j );
            }
        }
    }
}

void search_L(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for L tetriminos ..." << endl;

    // temp product is zero
    int temp_product = 0;

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i+1][j]*grid[i+1][j+1]*grid[i+1][j+2]*grid[i][j+2];
            if(temp_product > shape[5].product){
                set_struct(shape[5], temp_product, "Horizontal-Up", 'L', i, j );
            }
        }
    }

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i+1][j]*grid[i][j]*grid[i][j+1]*grid[i+0][j+2];
            if(temp_product > shape[5].product){
                set_struct(shape[5], temp_product, "Horizontal-Down", 'L', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j]*grid[i+1][j]*grid[i+2][j]*grid[i+2][j+2];
            if(temp_product > shape[5].product){
                set_struct(shape[5], temp_product, "Vertical-Right", 'L', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i+1][j+1]*grid[i+2][j];
            if(temp_product > shape[5].product){
                set_struct(shape[5], temp_product, "Vertical-Left", 'L', i, j );
            }
        }
    }
}

void search_O(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for O tetriminos ..." << endl;

    // temp product is zero
    int temp_product = 0;

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i+1][j]*grid[i+1][j+1];
            if(temp_product > shape[1].product){
                set_struct(shape[1], temp_product, "Square", 'O', i, j );
            }
        }
    }
}

void search_S(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for S tetriminos ..." << endl;

    // temp product is zero
    int temp_product = 0;

    for(int i = 1; i < rows-1; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j+1]*grid[i][j]*grid[i+1][j]*grid[i-1][j-1];
            if(temp_product > shape[3].product){
                set_struct(shape[3], temp_product, "Horizontal", 'S', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j]*grid[i+1][j]*grid[i+1][j+1]*grid[i+2][j+1];
            if(temp_product > shape[3].product){
                set_struct(shape[3], temp_product, "Vertical", 'S', i, j );
            }
        }
    }
}

void search_T(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for T tetriminos ..." << endl;

    // temp product is zero
    int temp_product = 0;

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i+1][j]*grid[i+1][j+1]*grid[i][j+1]*grid[i+1][j+2];
            if(temp_product > shape[6].product){
                set_struct(shape[6], temp_product, "Horizontal-Up", 'T', i, j );
            }
        }
    }

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i+1][j+1]*grid[i][j+2];
            if(temp_product > shape[6].product){
                set_struct(shape[6], temp_product, "Horizontal-Down", 'T', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j]*grid[i+1][j]*grid[i+1][j+1]*grid[i+2][j];
            if(temp_product > shape[6].product){
                set_struct(shape[6], temp_product, "Vertical-Right", 'T', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i+1][j]*grid[i+1][j+1]*grid[i][j+1]*grid[i+2][j+1];
            if(temp_product > shape[6].product){
                set_struct(shape[6], temp_product, "Vertical-Left", 'T', i, j );
            }
        }
    }
}

void search_Z(int **grid, tetrimonoe *shape, int rows, int cols){
    cout << "Searching for Z tetriminos ..." << endl;

    // temp product is zero
    int temp_product = 0;

    for(int i = 0; i < rows-1; i++){
        for(int j = 0; j < cols-2; j++){
            temp_product = grid[i][j]*grid[i][j+1]*grid[i+1][j+1]*grid[i+1][j+2];
            if(temp_product > shape[2].product){
                set_struct(shape[2], temp_product, "Horizontal", 'Z', i, j );
            }
        }
    }

    for(int i = 0; i < rows-2; i++){
        for(int j = 0; j < cols-1; j++){
            temp_product = grid[i][j+1]*grid[i+1][j+1]*grid[i+1][j]*grid[i+2][j];
            if(temp_product > shape[2].product){
                set_struct(shape[2], temp_product, "Vertical", 'Z', i, j );
            }
        }
    }
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
