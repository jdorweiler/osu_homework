/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 programming assignment # 1
** Resources Used:  I got the use of cmath to find the max values using pow() from the youtube video posted on blackboard
**			http://www.youtube.com/watch?v=bVcYlHaho8g&feature=youtu.be
**		    To convert binary numbers to decimal I used code from http://www.cplusplus.com/forum/windows/30135/ although I couldn't exactly
**			get that code to work so I made a few changes.  
**		    I got info on how to pass a string to the binaryToDec function using some info from this stackexchange post
			http://stackoverflow.com/questions/3903682/how-should-i-pass-a-stdstring-to-a-function
** Input: integer
** Output: Example output
****  Convert decimal number to binary and hex  ****
Decimal 9 Binary 00001001 Hex 0x9
Decimal 14 Binary 00001110 Hex 0xe
Decimal 42 Binary 00101010 Hex 0x2a
Decimal 96 Binary 01100000 Hex 0x60
***************************************************
****  Convert binary to hex and decimal ****
 Binary number 1110 is 14 in decimal and e in hex
 Binary number 11010 is 26 in decimal and 1a in hex
 Binary number 101010 is 42 in decimal and 2a in hex
 Binary number 1110100 is 116 in decimal and 74 in hex
****************************************************
***   Signed types  ********************************
Smallest short Dec: -32768 Hex -0x8000 oct -100000
Largest  short Dec: 32767 Hex 0x7fff oct 77777
Smalles int Dec: -2147483648 Hex -0x80000000 oct -20000000000
Largest int Dec: 2147483647 Hex 0x7fffffff oct 17777777777
Smalles long Dec: -9223372036854775808 Hex -0x8000000000000000 oct -1000000000000000000000
Largest long Dec: 9223372036854775807 Hex 0x7fffffffffffffff oct 777777777777777777777
****************************************************
***   Unsigned types *******************************
Smallest short Dec: 0 Hex 0x0 oct 0
Largest  short Dec: 65535 Hex 0xffff oct 177777
Smalles int Dec: 0 Hex 0x0 oct 0
Largest int Dec: 4294967295 Hex 0xffffffff oct 37777777777
Smalles long Dec: 0 Hex 0x0 oct 0
Largest long Dec: 18446744073709551615 Hex 0xffffffffffffffff oct 1777777777777777777777
****************************************************
Enter an integer 127
Your number 127 is Ox7f in Hex and 01111111 in binary 
****************************************************
******* Add One to overflow the max variables********
Short Max -32768
Int Max -2147483648
Long Max -9223372036854775808
Unsigned Short Max 0
Unsigned Int Max 0
Unsigned Long Max 0
******************************************************/
// including the libraries to use
#include <iostream> // used for cout, cin
#include <bitset> // used for convert into binary
#include <climits> // macros for the max/min variable types
#include <cmath> // pow() function used to calculate some of the max variables
#include <string.h> //second problem stored as strings.  Also to use c_str() for iterating through the binary numbers. 

// the numbers for the first two problems are stored in arrays
int decNumbers[] = {9,14,42,96};	// decimal numbers for first problem
const char* binNumbers[] = {"1110","11010","101010","1110100"};  // binary numbers for second problem

// set up the minimum variables using the climit macros
short short_Min = SHRT_MIN;		// smallest short
int int_Min = INT_MIN;			// smallest int
long long_Min = LONG_MIN;		// smallest long

// all of the unsigned minimums have to start at 0 
unsigned short ushort_Min = 0;		// the unsigned min for all are zero
unsigned int uint_Min = 0;
unsigned long ulong_Min = 0;

// There are macros for the max variables but I'm using pow() from the cmath library that I saw in the 
// supplimental class video posted on blackboard.  
signed short short_Max = (signed short)(pow(2.,sizeof(signed short)*8-1)); //the max is (type) 2^(sizeof(type)*8-1), one is subtracted since one bit is saved for 2's complement. 
signed int int_Max = (signed int)(pow(2.,sizeof(signed int)*8-1));
signed long long_Max = (signed long)(pow(2.,sizeof(long)*8-1));

unsigned short ushort_Max = (unsigned short)(pow(2.,sizeof(short)*8)); // the unsigned max using the same as above.  these are unsigned so no need to subtract 1 
unsigned int uint_Max = (unsigned int)(pow(2.,sizeof(int)*8));
unsigned long ulong_Max = (unsigned long)(pow(2.,sizeof(long)*8));

// use the std namespace so we can drop all the std::
using namespace std;

/*
This function is used to convert binary numbers to decimal for the second question on the assignment.  
A string is passed to the function.  The string is initialized with the a number from the binNumbers array which has the
binary numbers for the problem stored as strings. 
The FOR loop sets up the counter.  We start at zero and increase by one each loop up untill the counter
is less than the size of the string that we passed to it.  
In the IF statement we use c_str() to get the sequence of chars that make up the string so that we can iterate 
through it.  The counter is used to iterate through the characters and does a check to see if it is equal to 1.  
If the character is 1 we incriment the decimal variable by 2^( (size of the string - 1) - counter) since the
sequence of characters starts from the left. 
ex: Binary number 1001 = decimal 9
	2^(4-1-0) + 2^(4-1-3) = 2^3 + 2^1 = 8+1 = 9
Returns the decimal variable as a int. 
*/
int binaryToDec(const std::string& binary) 
{
	int decimal = 0;
	
	for (int counter = 0; counter < binary.size(); counter++){
		if(binary.c_str()[counter] == '1' ) {
			decimal += pow(2., (binary.size() - 1) - counter);
			//cout << decimal << " " << counter << " " << binary.size() <<endl; //debugging
		}
	}
	return decimal;
}

/*
This is the main part of the code.  The program starts here.  See comments below for more details on each part of the code.
*/
int main()
{	
	/* This is part one of the assignment.  Print the decimal numbers out as binary and hex.  loop through each number in decNumber array.  Convert to binary with bitset<8> for 8 bit binary numbers, then hex baseflag, set baseflag back to dec at the end of the line */
	cout << "****  Convert decimal number to binary and hex  ****" << "\n";
	for ( int i = 0; i < 4; i++) {
		// print out the results. 
		cout << "Decimal " << decNumbers[i] << " Binary " << bitset<8>(decNumbers[i]) << " Hex " << hex << "0x" << decNumbers[i] << dec << endl;
	}
	cout << "***************************************************" << "\n";
	/* This is part two.  Print the binary numbers out as decimal and hex.  Loop through each element in the binNumbers array. */
	cout << "****  Convert binary to hex and decimal ****" << "\n";
	for ( int i = 0; i < 4; i++) {
		int decimalNumber; // variable to hold the number returned from the binToDec function
		decimalNumber = binaryToDec(binNumbers[i]); // send binNumbers[i] string to the function and get a decimal back
		// print out the result
		cout << " Binary number " << binNumbers[i] << " is "  << decimalNumber << " in decimal and " << hex << decimalNumber << " in hex"<< dec << endl;
	}

	// Part 3. Print out the signed variables from climit and the max variables calculated at the top of the program.
	cout << "****************************************************" << "\n";
	cout << "***   Signed types  ********************************" << "\n";
	cout << "Smallest short Dec: "<< short_Min << " Hex "<< hex << "-0x"<<  short_Min<< " oct -" << oct << short_Min<< dec << endl;
	cout << "Largest  short Dec: " << short_Max << " Hex "<< hex << "0x"<<  short_Max<< " oct " << oct << short_Max<< dec << endl;
	cout << "Smalles int Dec: " << int_Min << " Hex "<< hex << "-0x"<< int_Min<< " oct -"<< oct << int_Min<< dec << endl;
	cout << "Largest int Dec: " << int_Max << " Hex "<< hex << "0x"<<  int_Max<< " oct "<< oct << int_Max<< dec << endl;
	cout << "Smalles long Dec: " << long_Min << " Hex "<< hex << "-0x"<< long_Min<< " oct -"<< oct << long_Min<< dec << endl;
	cout << "Largest long Dec: " << long_Max << " Hex "<< hex << "0x"<< long_Max<< " oct "<< oct << long_Max<< dec << endl;
	
	// Part 4. Print out the unsigned signed variables from climit and the max variables calculated at the top of the program.
	cout << "****************************************************" << "\n";
	cout << "***   Unsigned types *******************************" << "\n";
	cout << "Smallest short Dec: "<< ushort_Min << " Hex "<< hex << "0x"<<  ushort_Min<< " oct " << oct << ushort_Min<< dec << endl;
	cout << "Largest  short Dec: " << ushort_Max << " Hex "<< hex << "0x"<<  ushort_Max<< " oct " << oct << ushort_Max<< dec << endl;
	cout << "Smalles int Dec: " << uint_Min << " Hex "<< hex << "0x"<< uint_Min<< " oct "<< oct << uint_Min<< dec << endl;
	cout << "Largest int Dec: " << uint_Max << " Hex "<< hex << "0x"<<  uint_Max<< " oct "<< oct << uint_Max<< dec << endl;
	cout << "Smalles long Dec: " << ulong_Min << " Hex "<< hex << "0x"<< ulong_Min<< " oct "<< oct << ulong_Min<< dec << endl;
	cout << "Largest long Dec: " << ulong_Max << " Hex "<< hex << "0x"<< ulong_Max<< " oct "<< oct << ulong_Max<< dec << endl;
	cout << "****************************************************" << "\n";

	// Get a user integer and print in hex, bin.  The size of the integer is limited to 8 bit from the bitset<8>.
	int user_Int; // variable to hold the input
	cout << "Enter an integer "; // ask user for input
	cin >> user_Int; // store input
	cout << "Your number " << user_Int << " is Ox" << hex << user_Int << " in Hex and " << bitset<8>(user_Int) << " in binary " << dec << endl;
	cout << "****************************************************" << "\n";

	// Print all of the max variables plus one.  They will overflow since they are greater than the max.
	cout << "******* Add One to overflow the max variables********" << "\n";
	cout << "Short Max " << (short)(short_Max + 1) << endl; // short max is cast as a short to get it to overflow. It will just incriment otherwise
	cout << "Int Max " << int_Max + 1 << endl;
	cout << "Long Max " << long_Max + 1 << endl;
	cout << "Unsigned Short Max " << (short)(ushort_Max + 1) << endl; // unsigned short max cast as a short to get it to overflow. it will just incriment otherwise
	cout << "Unsigned Int Max " << uint_Max + 1 << endl;
	cout << "Unsigned Long Max " << ulong_Max + 1 << endl;

	cout << "******* Add One to overflow the min variables********" << "\n";
	cout << "Short Min " << (unsigned short)(short_Min - 1) << endl; // short max is cast as a short to get it to overflow. It will just incriment otherwise
	cout << "Int Min " << int_Min - 1 << endl;
	cout << "Long MIn " << long_Min - 1 << endl;
	cout << "Unsigned Short Min " << (unsigned short)(ushort_Min - 1) << endl; // unsigned short max cast as a short to get it to overflow. it will just incriment otherwise
	cout << "Unsigned Int Min " << uint_Min - 1 << endl;
	cout << "Unsigned Long Min " << ulong_Min - 1 << endl;

	return 0; // everything worked! send zero back 
}

