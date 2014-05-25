/******************************************************
** Author: Jason Dorweiler
** Date: 10-24-13
** Description: CS165 assignment 4
** Input: The user enters a string and follows the prompts.
** Output:

Enter a string to test
the cat is fat
 What do you want to do with it?
 [1] Reverse the string
 [2] Check to see if it is a palindrome 1
Would you like the [1] iterative or [2] recursive solution? 1
_____________________________________________________
Reverse the string with an iterative function
taf si tac eht
Try another? [1] Yes, [0] No
1
Enter a string to test
the cat is fat
 What do you want to do with it?
 [1] Reverse the string
 [2] Check to see if it is a palindrome 1
Would you like the [1] iterative or [2] recursive solution? 2
_____________________________________________________
Reverse the string with a recursive function
taf si tac eht
Try another? [1] Yes, [0] No
1
Enter a string to test
racecar
 What do you want to do with it?
 [1] Reverse the string
 [2] Check to see if it is a palindrome 2
Would you like the [1] iterative or [2] recursive solution? 1
_____________________________________________________
The iterative palindrome function says your string is a palindrome
Try another? [1] Yes, [0] No
1
Enter a string to test
racecar
 What do you want to do with it?
 [1] Reverse the string
 [2] Check to see if it is a palindrome 2
Would you like the [1] iterative or [2] recursive solution? 2
_____________________________________________________
The recursive palindrome function says your string is a palindrome
_____________________________________________________
Try another? [1] Yes, [0] No
0


*******************************************************/
#include <string>
#include <iostream>
#include <limits.h>

using namespace std;

string string_reverse(string, string); // iterative function that reverses strings
void recursive_reversed(string, string); //recursive function that reverses strings
bool is_palindrome_int(string); // iterative palindrome function
bool is_palindrome_recursive(string); // recursive palindrome function
void print_palindrome(string, bool); // function that prints the results from the two palindrome functions


int main(){

    string string_input; // string to hold the user input
    int run_type, func_type, run; // run_type-reverse or palindrome, func - iterative or recursive, run to loop again.
    run = 1; // set to 1 for the first time through.

    while(run){
        string reversed = ""; // string holding the reversed result. Declare in loop to reset it for the next loop

        //Get user string and find out what they want to do with it.
        cout << "Enter a string to test" << endl;
        getline(cin, string_input);
        cout << " What do you want to do with it?" << endl;
        cout << " [1] Reverse the string"  << endl;
        cout << " [2] Check to see if it is a palindrome ";
        cin >> run_type;
        cout << "Would you like the [1] iterative or [2] recursive solution? ";
        cin >> func_type;

        // clear out the buffer.  Seems to be required for this to work properly.
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        // this switch checks run_type to see if the user want to reverse the string or check
        // if it's a palindrome.  Inside we check the function type to print out the iterative
        // or recursive solution.
        switch (run_type) {
            case 1: {
                if(func_type == 1){
                    cout << "_____________________________________________________" << endl;
                    // reverse the string and store in reverse array
                    reversed = string_reverse(string_input, reversed);
                    cout << "Reverse the string with an iterative function" << endl;
                    cout << reversed << endl;
                }
                if(func_type == 2){

                    cout << "_____________________________________________________" << endl;
                    // reverse the string recursivly
                    cout << "Reverse the string with a recursive function" << endl;
                    recursive_reversed(string_input, reversed);
                }
                break;
            }
            case 2:{
                if(func_type == 1){
                    cout << "_____________________________________________________" << endl;
                    // is the string a palindrome
                    print_palindrome("The iterative palindrome function says your string", is_palindrome_int(string_input));
                }

                if(func_type == 2){
                    cout << "_____________________________________________________" << endl;
                    // is the string a palindrome recursive
                    print_palindrome("The recursive palindrome function says your string", is_palindrome_recursive(string_input));
                    cout << "_____________________________________________________" << endl;
                }
                break;
            }
        }
    // see if the user wants to run again.  Clear buffer again..
    cout << "Try another? [1] Yes, [0] No" << endl;
    cin >> run;
    cin.clear();
    cin.ignore(INT_MAX, '\n');

    }

return 0;

}

void print_palindrome(string str, bool result){
    // this function takes in a bool from the palindrome functions and prints out
    // if it was or was not a palindrome.
    cout << str;
    if(result){
        cout << " is a palindrome" << endl;
    }
    else{
        cout << " is not a palindrome" << endl;
    }
}

bool is_palindrome_int(string str){
    /*
    This function iterativly determines if a string is a palindrome.
    1. first check to see if it is only one character, palindrome by default
    2. loop through the length of the string.  Check the end chars if not equal, return false
    3. erase the two end chars and loop again
    */
    for(int i = 0; i <= str.length(); i++){
        if(str.length() == 1){
            return true;
        }
        if(str.at(0) != str.at(str.length()-1) && str.length() != 1){
            return false;
        }
        else{
            str.erase(str.size()-1);// take off the last char of the string
            str.erase(str.begin()); // take off the first char of the string.
        }
    }
return true;

}
bool is_palindrome_recursive(string str){
    /*
    This function check recursivly if the string was a palindrome.
    Stop condition is when the string is less than or equal to 1.
    Less than check the case when we started with an even number
    of characters.
    Check to see if the two end chars are the same.  If they are
    pull off the end chars and send the remaining string back to the
    function.  Return when the stop condition is met.
    */
    if(str.length() <= 1){
        return true;
    }
    if(str.at(0) != str.at(str.length()-1)){
        return false;
    }
    else{
        str.erase(str.begin()); // pull off the first char
        return is_palindrome_recursive(str.erase(str.size()-1)); // pull off the last char and call function again.
    }
}

void recursive_reversed(string string_input, string reversed){
    /*
     recursive function to reverse a string.  Stores the result in reversed string
     If lenght equal to one just return the char. Otherwise add the last char
     of the string to the reversed string.  Pull off the last char and call
     the function again with the new string. Return when we only have a string
     with one char.
    */
    if(string_input.length() == 1){
        reversed += string_input.at(0);
        cout << reversed << endl;
       return;
    }
    else{
        reversed += string_input.at(string_input.length()-1); // add char to reversed
        string_input = string_input.erase(string_input.size()-1); // pull off last char
        recursive_reversed(string_input, reversed);
    }
}

string string_reverse(string string_input, string reversed){
    // reverse string input by looping from 1 to lenght of the string.
    // Starting from the last char in the string and store in the
    // reverse array for printing out.
    for(int i = 1; i <= string_input.length(); i++){
        reversed += string_input.at(string_input.length()-i);
    }
return reversed;
}

