/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 programming lab 4 primes
** Input: number to check if it is prime
** Output:
Please enter a whole number:11
The number is a prime number.11

Please enter a whole number:10
The number is not a prime number.10

******************************************************/

#include <iostream>
#define PROMPT "Please enter a whole number:"
#define NOT_PRIME "The number is not a prime number."
#define PRIME "The number is a prime number."
#define DONE 0 /* ends successful program */
#define FIRST_FACTOR 2 /* initial value in for loop */ //start at 2 so we check number/2

using std::cout;
using std::cin;
int main()
{
    int i; /* loop counter */
    int number; /* number provided by user */
    cout << PROMPT; /* promt user */
    cin >> number; /* wait for user input */

    /* Prime numbers are defined as any number
    * greater than one that is only divisible
    * by one and itself. Dividing the number
    * by two shortens the time it takes to
    * complete. */

    for(i = FIRST_FACTOR; i < number/2; ++i)

    cout << "i: " << i << " number: " << number << " Mod: " << number%i << std::endl; // For Debugging

        if( number%i == 0 ) // Changed number/i to number%i so that the calculation works
        { /* if divisible */
            cout << NOT_PRIME << number << std::endl; /* not prime */
            return DONE; /* exit program */
        }

    /* if number is not divisible by anything
    * than it must be prime */
    cout << PRIME << number << std::endl;
    return 0;
}
