/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 Lab3 Random numbers
** Input: range for a random number
** Output:
Random number in range 0-99: 59
Random number in range 1-100: 52
Random number in range 1985-2014: 1999
Enter a new range for the random number generator.
Enter the lower bound
123
Enter the upper bound
123456
Your random number is: 46840 Range is 123-123456
******************************************************/

#include <iostream>
#include <cstdlib> // random numbers

using namespace std;

int main() {
    srand(time(0)); // seed the random number generator

    // print out some random numbers
    cout << "Random number in range 0-99: " << rand() %100 << endl;
    cout << "Random number in range 1-100: " << rand() %100 + 1 << endl;
    cout << "Random number in range 1985-2014: " << rand() %30 + 1985 << endl;

    // have user generate a random number
    int lower, upper;
    cout << "Enter a new range for the random number generator." << endl;
    cout << "Enter the lower bound" << endl;
    cin >> lower;
    cout << "Enter the upper bound" << endl;
    cin >> upper;
    cout << "Your random number is: " << rand() % (upper - lower) + lower << " Range is " << lower << "-" << upper << endl;

}
