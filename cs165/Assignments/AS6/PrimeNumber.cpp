/******************************************************
** Author: Jason Dorweiler
** Date: 11-10-13
** Description: CS165 Assignment 6
** Input: ./PrimeNumber then follow prompts
** Output:
***** Using the Prime Class *****
The default prime is 2
enter a prime number: 12
The new prime is 13
The next largest prime is 17
The next smallest prime is 11
*********************************

******************************************************/

#include "as6.h"

using AS6::PrimeNumber;

int main(int argc, char **argv)
{
    int primeN;

    // make a prime number
    PrimeNumber prime;

    cout << "***** Using the Prime Class *****" << endl;
    cout << "The default prime is " << prime.getPrime() << endl;

    cout << "Enter a prime number " << endl << "If not prime, then the next highest prime will be calculated for you: ";
    cin >> primeN;

    // set the prime number
    prime.setPrime(primeN);

    cout << "The new prime is " << prime.getPrime() << endl;

    // increase to the next prime.
    cout << "The next largest prime is " << ++prime << endl;

    // set the prime again and then decriment
    prime.setPrime(primeN);

    cout << "The next smallest prime is " << --prime << endl;

    cout << "*********************************" << endl;

}
