/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 Lab3 Flow Control
** Input: integer number
** Output: print out statement based on integer input
******************************************************/
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
	// variable to store input
	int input = 0;

	// explain what kind of input we want
	cout << "Please enter a number from 1 to 3: ";
	cin >> input;

	if ( input == 1) {
		cout << "you entered the number 1, perhaps the loneliest number." << endl;
	}

	else if ( input == 2 ) {
		cout << "You entered the number 2, perhaps the loneliest number since the number one." << endl;
	}

	else if ( input == 3 ) {
		cout << "you entered the number 3, making it the third wheel." << endl;
	}

	else {
		cout << "you entered some invalid input, next time try some valid input" << endl;
	}
	return 0;
}
