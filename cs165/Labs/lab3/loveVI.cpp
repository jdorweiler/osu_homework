/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 lab 3
** Input: enter an integer
** Output:
Do you like vi? enter 1 for true and 0 for false
1
You love vi!
******************************************************/

#include <iostream>

using std::cin; // user input
using std::cout; // screen output
using std::endl; // end line

int main(){

    int n = 0; // int for the user input

    cout << "Do you like vi? enter 1 for true and 0 for false" << endl;
    cin >> n; // read in input

    // check to see if n is 1 or 0 and display the result.
    if( n == 1){
        cout << "You love vi!" << endl;
            }
    if(n == 0){
        cout << "You hate vi!?" << endl;
    }
    return 0;
}
