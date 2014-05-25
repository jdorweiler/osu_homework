#include <iostream>
#include <climits>
#include <string>
#include <bitset>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;


void calculator();
void getInput(int &n, string s);

int main(int argc, char **argv){

    /******************************

    Calculator - binary, hex, 2s complement
    covering requirements 1-18

    ******************************/

    cout << "The first part of this program will work with binary" << endl
         << "hex and 2s complement number.  It covers the first 18" << endl
         << "requirements for the final. " << endl;

    calculator();

    return 0;
}

void calculator(){
    int decNum;
    int randN;

    // get a decimal number from the user
    getInput(decNum, "Please enter an integer number: ");
    cout << endl;

    /*
    * This part just shows the use of bitflags and converting between binary and hex
    * I included some print statements to show how the calculations work if done by
    * hand.
    */
    cout << "Lets convert the number to binary using 2^n for each bit. Ex:" << endl
    << "dec number 12 in binary is 1*8 + 1*4 +2*0+1*0 = 1100"<< endl <<
     "Your number is " << decNum << " in binary is " << std::bitset<8>(decNum) << endl << endl
    << "Lets convert your number to hex. Ex: decimal number 100 is 0x64 in hex which is 6*16+4 = 100"
    << endl << endl << "Your number in hex is " << std::hex << "0x" << decNum << std::dec << endl;


    /*
    *   2s complement reserves the left most bit for the sign of the number.
    *   Here is an example of doing 2s complement by hand:
    *
    *   -6+3 = -3
    *
    *   1010 = -6 in 2s complement
    * + 0011 = 3
    * -----------
    *   1101 = -3 in 2s complement
    *
    */

    //generate a negative random number for 2s complement calculation
    int randN = rand()%9-1;

    cout << "Lets do some 2s complement math with your number (see comments for hand calculation)" << endl
    << endl << std::bitset<8>(decNum) << " + " << std::bitset<8>(-6) << " = " << std::bitset<8>(decNum+(-6)) << endl;

}

void getInput(int &n, string s){
    // print the string and get input from the user
    cout << s;
    cin >> n;

    //check the input and ask for it again if there is
    //a problem.  Using the OR operator to check if there
    // is a cin problem or n is greater than the max int.
    while(!cin || n > INT_MAX){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << s;
        cin >> n;
    }
}
