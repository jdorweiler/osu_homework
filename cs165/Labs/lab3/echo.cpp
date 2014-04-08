/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 lab 1 assignment
** Input: user enters an int
** Output: prints the user entered int back out
ex:
Please enter a number to be printed: 
123
You entered: 123
******************************************************/

#include <iostream>

int main()
{	
	int input_value; // int variable to hold user input value

	std::cout << "Please enter a number to be printed: " << std::endl;
	std::cin >> input_value; // store input in int variable
	
	std::cout << "You entered: " << input_value << std::endl; //print the input back 

	return 0;
}
