/******************************************************
** Author: Jason Dorweiler
** Date: 10-17-13
** Description: CS165 Assignment 3
** Input: from the command line enter ./lab7 -f [<number>] -s [<number>]
** Output:
flip2 ~/labs/lab7 110% ./a.out -f 467 -s 1.23
 **** Pointer Fun ****
Using a Single Pointer ... The value and address of d1 is 7.8 and 0x601290
Using a Double Pointer ... The value and address of d1 is 7.8 and 0x601290
Using a Single Pointer ... The value and address of d2 is 10 and 0x601298
Using a Double Pointer ... The value and address of d2 is 10 and 0x601298
Using a Single Pointer ... The value and address of d3 is 0.009 and 0x6012a0
Using a Double Pointer ... The value and address of d3 is 0.009 and 0x6012a0
For option -f you entered 467
For option -s you entered 1.23

********************************************************/
#include <iostream>
#include <cstdlib> // used for atoi()

#define INPUT_MAX 100000 //limited the input from 1-100000
#define INPUT_MIN  1

using namespace std;

double dArr[] = {7.8, 10.0, 0.009}; // array for part one

int main(int argc, char* argv[]){
    cout << " **** Pointer Fun ****" << endl;

    double *d; // pointer d
    double **dp; // double pointer dp

    // loop from 1 to the number of thigns in the dArr array.
    for(int i = 1; i <= sizeof(dArr)/sizeof(double); i++){

        d = &dArr[i-1]; // set pointer to the address of the first thing in the dArr array

        // print out the first result by dereferancing the d pointer
        cout << "Using a Single Pointer ... ";
        cout << "The value and address of d" << i << " is " << *d << " and " << d << endl;

        dp = &d;// set the double pointer to the address of the single pointer

        // print out the value by dereferancing the double pointer with ** and the address with *
        cout << "Using a Double Pointer ... ";
        cout << "The value and address of d" << i << " is " << **dp << " and " << *dp << endl;

          }

         // for the second part of the lab. loop over the number of entries in the argc array.
        for(int i = 1; i < argc; i++){

            int int_argv;
            int_argv = argv[i][1];

            if(argv[i][0] == '-'){ // check for the "-" character

                //Check the next argv input where a number should be entered.  Restricted from 1 to INPUT_MAX
                // print out hint if the number is out of bounds
                if( atoi(argv[i+1]) <= 0 || atoi(argv[i+1]) > INPUT_MAX ){
                    cout<< "Usage: ./" << *argv[0] << " " << "[-f <number>] [-s <number>]  Number is from 1-100000" << endl;
                    return 0;
                }

                if(int_argv == 102){ // 102, ascii f
                    cout << "For option -f you entered "  << argv[i+1] << endl;
                }

                if(int_argv == 115){// 115, ascii s

                    cout << "For option -s you entered " << argv[i+1] << endl;
                }
        }
    }

return 0;
}


