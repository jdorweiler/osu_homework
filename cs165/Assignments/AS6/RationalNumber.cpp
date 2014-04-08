/******************************************************
** Author: Jason Dorweiler
** Date: 11-10-13
** Description: CS165 Assignment 6
** Input: ./RationalNumber then follow prompts
** Output:
Enter two integers: Numerator and denominator
2
4
Your rational number is 1/2
Lets make another rational number. Numerator and Denominator
1
7
Adding your two rational numbers
1/2+1/7=9/14

Subtracting your two rational numbers
1/2-1/7=5/14

Multiplying your two rational numbers
1/2*1/7=1/14

Dividing your two rational numbers
1/2 / 1/7=7/2

Checking if the two are equal
They are not equal

Is your first number less than your second?
No it is not

Is your first number less than or equal to your second?
No it is not

Is your first number greater than your second?
Yes it is

Is your first number greater than or equal to your second?
Yes it is

******************************************************/

   #include "as6.h"

   using AS6::RationalNumber;

   int main(){

    cout << "***** Using the Rational Class***" << endl;

    // make three rational numbers
    RationalNumber rational1, rational2, rational3;

    cout << "Enter two integers: Numerator and denominator " << endl;
    cin >> rational1;

    cout << "Your rational number is " << rational1 << endl;

    cout << "Lets make another rational number. Numerator and Denominator " << endl;
    cin >> rational2;

    cout << "Adding your two rational numbers" << endl;

    cout << rational1 << "+" << rational2 << "=" <<  rational1+rational2 << endl << endl;

    cout << "Subtracting your two rational numbers" << endl;

    cout << rational1 << "-" << rational2 << "=" <<  rational1-rational2 << endl << endl;

    cout << "Multiplying your two rational numbers" << endl;

    cout << rational1 << "*" << rational2 << "=" <<  rational1*rational2 << endl << endl;

    cout << "Dividing your two rational numbers" << endl;

    cout << rational1 << " / " << rational2 << "=" <<  rational1/rational2 << endl << endl;

    cout << "Checking if the two are equal" << endl;

    if(rational1 == rational2){
        cout << rational1 << "==" << rational2 << endl << endl << endl;
    }
    else {
        cout << "They are not equal" << endl << endl;
    }

    cout << "Is your first number less than your second? " << endl;

    if(rational1 < rational2){
        cout << "Yes it is" << endl << endl;
    }
    else {
        cout << "No it is not" << endl << endl;
    }

    cout << "Is your first number less than or equal to your second? " << endl;

    if(rational1 <= rational2){
        cout << "Yes it is" << endl << endl;
    }
    else {
        cout << "No it is not" << endl << endl;
    }

    cout << "Is your first number greater than your second? " << endl;

    if(rational1 > rational2){
        cout << "Yes it is" << endl << endl;
    }
    else {
        cout << "No it is not" << endl << endl;
    }

    cout << "Is your first number greater than or equal to your second? " << endl;

    if(rational1 >= rational2){
        cout << "Yes it is" << endl << endl;
    }
    else {
        cout << "No it is not" << endl << endl;
    }

   }
