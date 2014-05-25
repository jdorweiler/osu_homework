/******************************************************
** Author: Jason Dorweiler
** Date: 10-7-13
** Description: CS165 programming lab 5
** Input: two ints.  Separated by a space.  I'm using a space
delimiter for the getline() so enter wont work.  For some reason
using getline with the delimiter was causing problems that I couldn't
figure out.  It could run one through just fine but the second time
through it would skip the second user input.
** Output:
please enter 2 ints. example 3 9,  the space is important!
3 9
0 1 2 3
3 2 1 0
3 4 5 6 7 8 9
Do you want to run this again with 2 different ints? (Enter 1 for yes, 2 for no)
0
******************************************************/

#include <iostream>
#include <string>
#include <cstdlib> // for atoi()

using namespace std;

//forward declarations
//counter functions
void counterOne(int n1);
void counterTwo(int n1);
void counterThree(int n1, int n2);

//gets user input
int get_positive_int();

// converts to int and checks to see if it is positive
bool is_positive_int(string input);

// global string objects
string n1, n2;

// global int numbers entered by the user
int int_n1, int_n2;

int main(){

    int replay = 1;

    // start again.
    while(replay == 1){
        n1.clear(); // clear out the strings
        n2.clear();
        get_positive_int(); // gets data from user and does some error checking on the input
        counterOne(int_n1);
        counterTwo(int_n1);
        counterThree( int_n1, int_n2 );

        cout << "Do you want to run this again with 2 different ints? (Enter 1 for yes, 2 for no)" << endl;
        cin >> replay;

    }

}

bool is_positive_int(string n1, string n2){
    int_n1 = atoi(n1.c_str()); // convert string to int
    int_n2 = atoi(n2.c_str());

    // return true if any are not positive
    if (int_n1 < 0){
        return true;
    }
    if (int_n2 < 0){
        return true;
    }
    else {
        return false; // return false, they are positive ints
    }
}


int get_positive_int(){
    // This gets the user input using getline() then call the is positive function and checks to see if the number
    // are positive

    cout << "please enter 2 ints. example 3 9,  the space is important!" << endl;
   // cout << atoi(n1.c_str()) << " " << atoi(n2.c_str()) << endl; // dubugging

   // getline(cin, n1) // this doesn't work! causes problems on the 2nd run.
    getline(cin, n1, ' '); // space delimited,
    getline(cin, n2);

    // check to see if the ints are positive by calling the is_positive_in function. returns true if one is negative.
    while((is_positive_int(n1, n2))){
        cout << " *** That value is invalid, please enter positive numbers***" << endl;
        get_positive_int(); // get user input agains
    }

    return 0;
}

void counterOne(int n1){
    // count from 0 to n1, n1+1 each time through
    for(int i = 0; i < n1+1; i++){
        cout << i << " ";
    }
cout << endl;
}

void counterTwo(int n1){
    // count from n1 to 0, n1-1 each time through
    for(int i = n1; i >= 0; i--){
        cout << i << " ";
    }
cout << endl;
}

void counterThree(int n1, int n2){
    // first check to see which is greater
    if(n1 < n2){
        // count from n1 up to n2, add one each time through the loop
        for(int i = n1; i <= n2; i++){
        cout << i << " ";
        }
    }

    if(n1 > n2){
        // count down from n1 to n2, decrease by one each time through the loop
        for(int i = n1; i >= n2; i--){
        cout << i << " ";
        }
    }

cout << endl;
}

