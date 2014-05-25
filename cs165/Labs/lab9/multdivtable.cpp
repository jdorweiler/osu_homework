/******************************************************
** Author: Jason Dorweiler
** Date: 10-25-13
** Description: CS165 lab 9
** Input: ./multdivtable 5 5
** Output:
Multiplication Table:
1 , 2 , 3 , 4 , 5
2 , 4 , 6 , 8 , 10
3 , 6 , 9 , 12 , 15
4 , 8 , 12 , 16 , 20
5 , 10 , 15 , 20 , 25

Division Table:
1 , 0.5 , 0.333333 , 0.25 , 0.2
2 , 1 , 0.666667 , 0.5 , 0.4
3 , 1.5 , 1 , 0.75 , 0.6
4 , 2 , 1.33333 , 1 , 0.8
5 , 2.5 , 1.66667 , 1.25 , 1


*******************************************************/
#include <iostream>
#include <cstdlib>
using namespace std;

// struct that holds the multiplication and division results
struct multi_div_value{
    int mult;
    float div;
};


void setup_table(multi_div_value **&table, int height, int width); // creates a array of structs
void set_table_values(multi_div_value **table, int i, int width); // this loops through the rows of the table
void fill_table(multi_div_value *table, int level, int width); // this loops through the columns and call the mult and div functions
void delete_table(multi_div_value **table, int height); // delete the table
void print_table(multi_div_value **table, int height, int width, int type); // prints the table, type is 0 for mult, 1 for div
void set_mult(multi_div_value &table, int level, int i); // calculate the multiplication value for that spot
void set_div(multi_div_value &table, int level, int i); // calculate the division value for that spot

int main(int argc, char *argv[]){

    // get height and width of the table
    int height = atoi(argv[1]);
    int width = atoi(argv[2]);

    // declare struct
    multi_div_value **table;

    // this function creates the array of structs
    setup_table(table, height, width);

    // this function calls the multiplication and division functions
    set_table_values(table, height, width);

    // print out both tables.
    cout << "Multiplication Table:" << endl;
    print_table(table, height, width, 0);
    cout << endl;
    cout << "Division Table:" << endl;
    print_table(table, height, width, 1);

    // delete the tables
    delete_table(table, height);

return 0;
}

void print_table(multi_div_value **table, int height, int width, int type){
    //Prints out the tables.  This function loops through the height and then width of the
    // table and prints out either the mult or div values base on the int type that it is given
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(type == 0){
            cout << table[i][j].mult;
            }
            if(type == 1){
                cout <<  table[i][j].div;
            }
            if(j % width != width -1 ){
                cout << " , ";
            }
        }
        cout << endl;
    }
}

void setup_table(multi_div_value **&table, int height, int width){
    /*
    This function sets up the array of structs.  It makes an array of
    pointers to the number of rows (height) that we want.  Then creates
    and array of structs based on the width that we want.
    */
    table = new multi_div_value*[height];
        for(int i = 0; i < height; i++){
        table[i] = new multi_div_value[width];
    }
}

void set_table_values(multi_div_value **table, int height, int width){
    // loop through the rows of the table and send each row to the fill table function.
    for(int i =0; i < height; i++){
        fill_table(table[i], i+1, width);
    }
}

void fill_table(multi_div_value *table, int level, int width){
    // loop through the width of the table and call the mult and div functions to set
    // the values.
    for(int i = 0; i < width; i++){
        set_mult(table[i], level, i);
        set_div(table[i], level, i);
    }
}

void set_mult(multi_div_value &table, int level, int i){
    // calculates the mult values at a given  position
    table.mult = level+i*level;
}

void set_div(multi_div_value &table, int level, int i){
    // calculates the div values at a given position
        table.div = (float)level - i*float(level/(i+1.0));
}
void delete_table(multi_div_value **table, int height){
    // delete the table by iterating through it and using delete
        for(int i = 0; i < height; i++){
            delete table[i];
        }
        delete [] table;
}
