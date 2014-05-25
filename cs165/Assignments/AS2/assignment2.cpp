/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 programming assignment # 2
** Resources Used:
** Input:
** Output:
******************************************************/
// including the libraries to use
#include <iostream> // used for cout, cin
#include <climits> // macros for the max/min variable types
#include <cmath> // pow() function used to calculate some of the max variables

// set up the minimum variables using the climit macros
short short_Min = -1*(pow(2.,sizeof(short)*8))-1;		// smallest short
int int_Min = -1*(pow(2.,sizeof(int)*8))-1; // smallest int
long long_Min = -1*(pow(2.,sizeof(long)*8))-1;// smallest long

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

int main(){
	// Print all of the max variables plus one.  They will overflow since they are greater than the max.
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

