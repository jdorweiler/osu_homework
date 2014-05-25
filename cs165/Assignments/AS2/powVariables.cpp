/******************************************************
** Author: Jason Dorweiler
** Date: 10-10-13
** Description: CS165 programming assignment # 2
** Input: none
** Output:
******* Signed Variables********
Short Max 32767
Short Min -32768
Int Max 2147483647
Int Min -2147483648
Long Max 9223372036854775807
Long Min -9223372036854775808
******* Unsigned Variables********
UShort Max 65535
UInt Max 4294967295
ULong Max 18446744073709551615

******************************************************/
// including the libraries to use
#include <iostream> // used for cout, cin
#include <climits> // macros for the max/min variable types
#include <cmath> // pow() function

// using pow() to calculate the max and min variable types
// ex:  2^(sizeof(short)*8) = 2^16 since sizeof(short) is 2.
short short_Min = (short)-1*(pow(2.,sizeof(short)*8-1));		// smallest short
int int_Min = (int)-1*(pow(2.,sizeof(int)*8-1)); // smallest int
long long_Min = (long)-1*(pow(2.,sizeof(long)*8-1));// smallest long

short short_Max = (short)(pow(2.,sizeof(signed short)*8-1)); //the max is (type) 2^(sizeof(type)*8-1), one is subtracted since one bit is saved for 2's complement.
int int_Max = (int)(pow(2.,sizeof(signed int)*8-1));
long long_Max = (long)(pow(2.,sizeof(long)*8-1));

unsigned short ushort_Max = (unsigned short)(pow(2.,sizeof(short)*8)); // the unsigned max using the same as above.  these are unsigned so no need to subtract 1
unsigned int uint_Max = (unsigned int)(pow(2.,sizeof(int)*8));
unsigned long ulong_Max = (unsigned long)(pow(2.,sizeof(long)*8));

// use the std namespace so we can drop all the std::
using namespace std;

int main(){
	// Print everything out
	cout << "******* Signed Variables********" << "\n";
	cout << "Short Max " << short_Max  << endl;
	cout << "Short Min " << short_Min << endl;
	cout << "Int Max " << int_Max << endl;
	cout << "Int Min " << int_Min << endl;
    cout << "Long Max " << long_Max << endl;
	cout << "Long Min " << long_Min << " " << endl;
	cout << "******* Unsigned Variables********" << "\n";
	cout << "UShort Max " << ushort_Max  << endl;
	cout << "UInt Max " << uint_Max << endl;
    cout << "ULong Max " << ulong_Max << endl;


	return 0; // everything worked! send zero back
}

