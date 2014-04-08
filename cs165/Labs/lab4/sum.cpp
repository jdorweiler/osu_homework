/******************************************************
** Author: Jason Dorweiler
** Date: 10-9-13
** Description: CS165 programming lab 4 summation
** Input: highest number to sum to for sum(x^5+10,1,input)
** Output:
What value would you like to stop the sum over the function x^5 + 1?
1
The total is 11
Would you like to try another to sum up to?
Enter 0 for no or 1 for yes 1
What value would you like to stop the sum over the function x^5 + 1?
2
The total is 53
Would you like to try another to sum up to?
Enter 0 for no or 1 for yes 1
What value would you like to stop the sum over the function x^5 + 1?
3
The total is 306
Would you like to try another to sum up to?
Enter 0 for no or 1 for yes 0

******************************************************/

#include <cmath>
#include <iostream>
#include <limits.h> // for INT_MAX in input error checking

#define MAX_N 47 // max number with causing overflow

using namespace std;

int main(){

    // set initial to 1 so that we start the calculation once.
    int run_again = 1;

    // continue looping untill the user wants to stop
    // while loops keep running while the expression is true so no need to check
    while(run_again){

        int total = 0;
        int inputVar = 0;

        cout << "What value would you like to stop the sum over the function x^5 + 1?" << endl;
        cin >> inputVar;

        // check to see that we got valid input. must be between 1 and MAX_N to pass
        // If it's not valid, clear out the error state and discard the characters in the stream.
        while(inputVar < 1 || inputVar > MAX_N || !cin){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " *** That value is invalid, please enter a value from 1 through " << MAX_N << " ***"<< endl;
            cin >> inputVar;

        }

        // calculate sum of x^5+10 from 1, to user input
        for( int i = 1; i < inputVar+1; i++){

            total += pow(i,5) + 10;

        }

        //check to see if the user wants to run again.
        cout << "The total is " << total << endl;
        cout << "Would you like to try another to sum up to?" << endl << "Enter 0 for no or 1 for yes ";
        cin >> run_again;
    }

}
