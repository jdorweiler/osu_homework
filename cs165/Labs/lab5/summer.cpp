/******************************************************
** Author: Jason Dorweiler
** Date: 10-7-13
** Description: CS165 programming lab 5 summation with Functions! And optional extra functions
** Input: number to sum
** Output:
What value would you like to stop the sum over the function x^5 + 1?
3
Your total is 306
Would you like to try another to sum up to?
Enter 0 for no or 1 for yes 1
What value would you like to stop the sum over the function x^5 + 1?
45
Your total is 1477933875
Would you like to try another to sum up to?
Enter 0 for no or 1 for yes 0

******************************************************/

#include <cmath>
#include <iostream>

#define MAX_N 47 // max number with out causing overflow

using namespace std;

// forward declaration so compiler knows we are using some functions
int summer(); // sum function that calculates and returns the total
void printTotal(int total); // function to for printing
int runAgain(); // function to check to see if we want to run again.

int main(){

    int run_again = 1; // initialize so we run once

    // loop while true
    while(run_again){

    //get total
    int total = summer();
    // print total
    printTotal(total);
    // check to run again?
    run_again = runAgain();
    }

}
// function that checks to see if the user wants to run again, returns bool
int runAgain(){
    int run_again;
    cout << "Would you like to try another to sum up to?" << endl << "Enter 0 for no or 1 for yes ";
    cin >> run_again;
    return run_again;
}
// printing funciton
void printTotal(int total){

    cout << "Your total is " << total << endl;
}
// summing function same as in lab 4, returns the total
int summer(){


    int total = 0;
    int inputVar = 0;

    cout << "What value would you like to stop the sum over the function x^5 + 1?" << endl;
    cin >> inputVar;

    // check to see that we got valid input. must be between 1 and MAX_N to pass
    while(inputVar < 1 || inputVar > MAX_N){

        cout << " *** That value is invalid, please enter a value from 1 through " << MAX_N << " ***"<< endl;
        cin >> inputVar;

    }

    // calculate sum of x^5+10 from 1, to user input
    for( int i = 1; i <=inputVar; i++){
        total += pow(i,5) + 10;
    }

return total;
}
