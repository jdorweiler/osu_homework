#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <climits>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void printArray(int *array, int width);
void calculator();
void arrays();
void getInput(int &n, string s, int max);
void setup_array(int **&arr, int height, int width);
void print2DArray(int **arr, int height, int width);

int main(int argc, char **argv){

    int next;

    /******************************
    Calculator - binary, hex, 2s complement
    covering requirements 1-18
    ******************************/

    cout << "*****************************************************" << endl;
    cout << "The first part of this program will work with binary" << endl
         << "hex and 2s complement number.  It covers the first 18" << endl
         << "requirements for the final. " << endl;

    calculator();

    cin.ignore();
    cout << "Press ENTER to continue" << endl;
    cin.ignore(INT_MAX, '\n');

    /******************************************
    The second part of this program plays around
    with arrays, 1d, 2d, static, and dynamic
    ******************************************/

    cout << "*****************************************************" << endl;
    cout << "The second part of this program will work with arrays" << endl
         << "and recursion" << endl << endl;

    arrays();

    /******************************************
    The third part of this program covers the
    remaining requirements for the final.  It
    uses the ShoppingMall namespace to create
    stores of different types (subclasses).  They
    are stored in a vector of shared pointers
    and printed to the screen and a file using
    overloaded ostream operator.
    *******************************************/



    return 0;
}

void arrays(){
    int width = 5;
    int height;
    int *array = new int[width];

    for(int i = 0; i < width; ++i){
        array[i] = rand()%9-1;
    }

    cout << "A static array was declared, filled with random" << endl
         << "integers and printed with the recursive function" << endl << endl;

    cout << "The random static array of 5 integers is:" << endl;
    printArray(array, 5);

    delete [] array;

    cout << "Lets make a dynamic 2d array" << endl;
    getInput(width, "enter the width from 1-9: ", 9);
    getInput(height, "enter the height from 1-9: ", 9);

    int **array2D;

    setup_array(array2D, height, width);

    print2DArray(array2D, height, width);

}

void setup_array(int **&arr, int height, int width){
    arr = new int*[height];

    for(int i = 0; i < height; i++){
        arr[i] = new int[width];
        for(int j = 0; j < width; ++j){
            arr[i][j] = rand()%100-1;
        }
    }

}

void print2DArray(int **arr, int height, int width){
    for(int i = 0; i < height; i++){
        cout << "[";
        for(int j = 0; j < width; j++){
            cout << std::setw(2) << arr[i][j];
            if(j % width != width -1 ){
                cout << " , ";
            }
        }
        cout << "]" << endl;
    }

}

void printArray(int *array, int width){
        if(width == 0){
            return ;
        }
        else{
            printArray(array, --width);
        }
        cout << array[width] << " ";
}
void calculator(){
    std::srand(time(0));

    int decNum;
    int randN;

    // get a decimal number from the user
    getInput(decNum, "Please enter an integer number from 1-255 (to keep bin numbers small): ", 255);
    cout << endl;

    /*
    * This part just shows the use of bitflags and converting between binary and hex
    * I included some print statements to show how the calculations work if done by
    * hand.
    */
    cout << "Lets convert the number to binary using 2^n for each bit. Ex:" << endl
    << "dec number 12 in binary is 1*8 + 1*4 +2*0+1*0 = 1100"<< endl <<
     "Your number is " << decNum << " in binary is " << std::bitset<8>(decNum) << endl << endl
    << "Lets convert your number to hex. Ex: decimal number 100 is 0x64 in hex which is 6*16+4 = 100"
    << endl << "Your number in hex is " << std::hex << "0x" << decNum << std::dec << endl << endl;


    /*
    *   2s complement reserves the left most bit for the sign of the number.
    *   Here is an example of doing 2s complement by hand:
    *
    *   -6+3 = -3
    *
    *   1010 = -6 in 2s complement
    * + 0011 = 3
    * -----------
    *   1101 = -3 in 2s complement
    *
    */

    //generate a negative random number for 2s complement calculation
    randN = -rand()%9-1;

    cout << "Lets do some 2s complement math with your number" <<
    " and a random negative number (see comments for hand calculation)" << endl
    << decNum << " + " << randN << " = " << decNum+randN << endl
    << endl << std::bitset<8>(decNum) << " + " << std::bitset<8>(randN) << " = " << std::bitset<8>(decNum+(randN)) << endl;
    cout << "*****************************************************" << endl;
}

void getInput(int &n, string s, int max){
    // print the string and get input from the user
    cout << s;
    cin >> n;

    //check the input and ask for it again if there is
    //a problem.  Using the OR operator to check if there
    // is a cin problem or n is greater than the max int.
    while(!cin || n > max || n < 0){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << s;
        cin >> n;
    }
}
