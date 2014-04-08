/******************************************************
** Author: Jason Dorweiler
** Date: 11-2-13
** Description: CS165 Assignment 5
** Input: ./product -rows 5 -cols 6
** Output:
row #0  [55 , 30 , 92 , 06 , 25 , 37]
row #1  [18 , 89 , 12 , 08 , 49 , 83]
row #2  [19 , 20 , 47 , 29 , 08 , 60]
row #3  [32 , 98 , 39 , 84 , 06 , 88]
row #4  [33 , 97 , 61 , 47 , 86 , 44]

Starting Search
Searching for I tetriminos ...
Searching for J tetriminos ...
Searching for L tetriminos ...
Searching for O tetriminos ...
Searching for S tetriminos ...
Searching for T tetriminos ...
Searching for Z tetriminos ...

Max Prod: 31141656 Row: 3 Col: 1 Shape: L, Horizontal Down


*******************************************************/
#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

// struct to keep track of the greatest product for each type
struct tetrimonoe{
    char type; // type of tetrimonoe i.e. 'L' 'T' ..
    string position; // the rotation orientation of the tetrimonoe.  See write up PDF for more about this
    int product;
    int row;
    int col;
    tetrimonoe(): product(0) {} // set initial product to zero for all tetrimonoes
};

void setColor(int **color, int i, int j, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void create_random_grid(int **&grid, int rows, int cols); // creates the 2D matrix and fills with random ints from 0-99
void print_grid(int **grid, int rows, int cols); // print out the random grid
void search_grid(int **grid, tetrimonoe *shape, int rows, int cols); // this function call all the other search functions
void set_struct(tetrimonoe &shape, int temp_product, string position, char type, int row, int col); // for easily setting struct parameters
void print_result(tetrimonoe *product); // searches all of the structs and prints out the one with the largest product
void delete_grid(int **grid, int rows); // deletes the matrix using Delete
int errorChecker(char **argv, int argc); // check the argv input
void get_input(int &rows, int &cols, char **argv); // get the argv input

// Search functions for each tetrimonoe
void search_I(int **grid, tetrimonoe *shape, int rows, int cols);
void search_J(int **grid, tetrimonoe *shape, int rows, int cols);
void search_L(int **grid, tetrimonoe *shape, int rows, int cols);
void search_O(int **grid, tetrimonoe *shape, int rows, int cols);
void search_S(int **grid, tetrimonoe *shape, int rows, int cols);
void search_T(int **grid, tetrimonoe *shape, int rows, int cols);
void search_Z(int **grid, tetrimonoe *shape, int rows, int cols);

// Main search that is used by each of the tetrimone search functions above.
void main_search(int **grid, tetrimonoe &shape, int rows, int cols, int rowVal, int colVal, string orientation, char type,  int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

int main(int argc, char **argv) {

    // Check argv for input errors first.
    if (errorChecker(argv, argc)){
        return 1;
    }

    int rows, cols;

    // read the argv input set to the row and col values
    get_input(rows, cols, argv);

    // array for the 2D grid
    int **grid;

    // structs to keep track of shapes. One struct for
    // each of the 7 tetrimones
    tetrimonoe shape[7];

    // create the grid and fill with random ints
    create_random_grid(grid, rows, cols);

    // print the grid
    print_grid(grid, rows, cols);

    // search grid
    search_grid(grid, shape, rows, cols);

    // find the shape with the largest product and print it out.
    print_result(shape);

    // delete the 2d grid
    delete_grid(grid, rows);


return 0;
}

void search_grid(int **grid, tetrimonoe *shape, int rows, int cols){
    /*

    Search the grid for the greatest product of the tetris tetrimino shapes
    http://en.wikipedia.org/wiki/Tetris#Colors_of_Tetriminos

    Takes the grid, shape structs, cols, and rows and passed them onto the
    search for the individual shapes.  This is a good place to comment out specific
    searches to validate that they are working.
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
    /*
    Helper function to setup the structs
    */
    shape.product = temp_product;
    shape.position = position;
    shape.type = type;
    shape.row = row;
    shape.col = col;

}

void main_search(int **grid, tetrimonoe &shape, int rows, int cols, int rowVal, int colVal, string orientation, char type,  int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    /*
    This is the main search function.  It takes the grid, shape struct, rows, cols.
    It then takes in several parameters that set how the two FOR loops will run.  The
    rowVal and colVal will set how far through the rows or column we need to loop through
    this is based on the size of the shape that we are checking.  Next it get the x,y
    coordinates for where the shape is inside of a 3x3 grid. See write up for more on
    this.
    It calculates the temp product at each point and if it is larger then what is already
    stored for that struct it will update the struct with the new product and location,
    orientation of the new shape.

    */
    int temp_product = 0;
    for(int i = 0; i < rows-rowVal; i++){
        for(int j = 0; j < cols-colVal ; j++){
     //    cout << "The value of row: " << i << " column: " << j << " is " << grid[i][j] << endl;
            temp_product = grid[i+x1][j+y1]*grid[i+x2][j+y2]*grid[i+x3][j+y3]*grid[i+x4][j+y4];
          //  cout << "start " << grid[i][j] << " " << "product " << temp_product << endl;
            if(temp_product > shape.product){
                set_struct(shape, temp_product, orientation , type, i+x1, j+x2);

            }
        }
    }
}

void search_I(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for I tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for I tetriminos ..." << endl;

   main_search(grid, shape[0], rows, cols, 3, 0, "0 Degrees", 'I', 0, 0, 1, 0, 2, 0, 3, 0);

   main_search(grid, shape[0], rows, cols, 0, 3, "180 Degrees", 'I', 0, 0, 0, 1, 0, 2, 0, 3);

}

void search_J(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for J tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for J tetriminos ..." << endl;
    main_search(grid, shape[4], rows, cols, 1, 2, "270 degrees", 'J', 0, 0, 1, 0, 1, 1, 1, 2);

    main_search(grid, shape[4], rows, cols, 1, 2, "90 Degrees", 'J', 0, 0, 0, 1, 0, 2, 1, 2);

    main_search(grid, shape[4], rows, cols, 2, 1, "0 Degrees", 'J', 0, 1, 1, 1, 2, 1, 2, 0);

    main_search(grid, shape[4], rows, cols, 2, 1, "180 Degrees", 'J', 0, 0, 0, 1, 1, 0, 2, 0);

}

void search_L(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for L tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for L tetriminos ..." << endl;
    main_search(grid, shape[5], rows, cols, 1, 2, "Horizontal Up", 'L', 1, 0, 1, 1, 1, 2, 0, 2);

    main_search(grid, shape[5], rows, cols, 1, 2, "Horizontal Down", 'L', 1, 0, 0, 0, 0, 1, 0, 2);

    main_search(grid, shape[5], rows, cols, 2, 1, "Vertical Up", 'L', 0, 0, 1, 0, 2, 0, 2, 2);

    main_search(grid, shape[5], rows, cols, 2, 1, "Vertical Down", 'L', 0, 0, 0, 1, 1, 1, 2, 1);

}

void search_O(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for O tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for O tetriminos ..." << endl;
    main_search(grid, shape[1], rows, cols, 1, 1, "Square", 'O', 0, 0, 0, 1, 1, 0, 1, 1);

}

void search_S(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for S tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for S tetriminos ..." << endl;
    main_search(grid, shape[3], rows, cols, 1, 2, "Horizontal", 'S', 1, 0, 1, 1, 0, 1, 0, 2);

    main_search(grid, shape[3], rows, cols, 2, 1, "Vertical", 'S', 0, 0, 1, 0, 1, 1, 2, 1);

}

void search_T(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for T tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for T tetriminos ..." << endl;
    main_search(grid, shape[6], rows, cols, 1, 2, "Horizontal Up", 'T', 1, 0, 1, 1, 0, 1, 1, 2);

    main_search(grid, shape[6], rows, cols, 1, 2, "Horizontal Down", 'T', 0, 0, 0, 1, 1, 1, 0, 2);

    main_search(grid, shape[6], rows, cols, 2, 1, "Vertical Right", 'T', 0, 0, 1, 0, 1, 1, 2, 0);

    main_search(grid, shape[6], rows, cols, 2, 1, "Vertical Left", 'T', 1, 0, 1, 1, 0, 1, 2, 1);

}

void search_Z(int **grid, tetrimonoe *shape, int rows, int cols){
    /*
    Search for Z tetrimonoes.  Call the main search using the xy coordinates
    of the two orientations.
    */
    cout << "Searching for Z tetriminos ..." << endl;
    main_search(grid, shape[2], rows, cols, 1, 2, "Horizontal", 'Z', 0, 0, 0, 1, 1, 1, 1, 2);

    main_search(grid, shape[2], rows, cols, 2, 1, "Vertical", 'Z', 0, 1, 1, 1, 1, 0, 2, 0);

    cout << endl;
}

void create_random_grid(int **&grid, int rows, int cols){
    /*
    Create the random 2D grid based on the number of rows and columns needed
    fill the grid with random ints using rand() from 0-99
    */
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
    /*
    This function just prints out the random grid by looping
    through all the rows and columns and printing out the value
    at each point.
    */
    for(int k = 0; k < cols; k++){
        cout << "    " << k+1;
    }
    cout << endl;
    for(int i = 0; i < rows; i++){
        cout << i + 1<< "  [";
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
        for(int i = 0; i < rows; i++){
            delete grid[i];
        }
        delete [] grid;
}

int errorChecker(char **argv, int argc){
    /*
    Error checking argv.  rows and cols cant be less than 4
    and this will also check for a number since atoi will cause an error
    for anything else.
    */
    if( argc < 3 || !(atoi(argv[2]) >= 4) || !(atoi(argv[4]) >= 4)){
        cout << "Correct usage is:  ./program [-rows <#rows>] [-cols <#columns>]" << endl;
        return 1;

    }
return 0;
}

void get_input(int &rows, int &cols, char **argv){
    /*
    Check the 1st and 3rd elements in argv and assign
    rows and cols.  Use string compare (strcmp) to compare
    the two strings.
    */

    if(strcmp(argv[3], "-rows")){
        rows = atoi(argv[2]);
        cols = atoi(argv[4]);
    }

    if(strcmp(argv[1], "-rows")){
        rows = atoi(argv[4]);
        cols = atoi(argv[2]);
    }
}

void print_result(tetrimonoe *shape){
    /*
    This function just searches through the 7
    shapes and pick the one with the largest
    product.  It prints out the result
    */
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
