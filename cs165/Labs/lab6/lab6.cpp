/******************************************************
** Author: Jason Dorweiler
** Date: 10-14-13
** Description: CS165 lab 6
** Input: Two integers and a word to check if it is a palindrome
** Output:
Enter first number 4
Enter second number 7
Adding two numbers with iterative solution 11
Adding two numbers with recursive solution 11
Multiply two numbers with iterative solution 28
Multiply two numbers with iterative solution 28
Enter a word to check if it's a palindrome:
racecar
racecar is a palindrome

*/

#include <iostream>
#include <string>
#include <limits.h>

using std::cout;
using std::endl;
using std::cin;
using std::string;

// forward declarations
int add_it(int, int);
int add_rec(int, int);
int mult_it(int, int);
int mult_rec(int, int, int current = 0); // default for current is zero
bool is_pal(string, int);

int main()
{
    // set up variables
    int operand1 = 0, operand2 = 0 ;
    string word;

    // get two numbers
    cout << "Enter first number ";
    cin >> operand1;
    cout << "Enter second number ";
    cin >> operand2;

    // add and multlply two numbers using iterative and recursive solutions
    cout << "Adding two numbers with iterative solution " << add_it(operand1, operand2) << endl;
    cout << "Adding two numbers with recursive solution " << add_rec(operand1, operand2) << endl;
    cout << "Multiply two numbers with iterative solution " << mult_it(operand1, operand2) << endl;
    cout << "Multiply two numbers with iterative solution " << mult_rec(operand1, operand2) << endl;
    cout << "Enter a word to check if it's a palindrome: " << endl;

    // clear input buffer
    cin.clear();
    cin.ignore(INT_MAX, '\n');

    // get a string
    getline(cin, word);

    // is the word a palindrome?
    if(is_pal(word, word.length())){
        cout << word << " is a palindrome" << endl;;
    }
    else{
        cout << word << " is not a palindrome" << endl;;
    }
    return 0;
}

bool is_pal(string word, int word_length){
   /*
    This function checks to see of a word is a palindrome
    It works recursivly calling the function again and sending
    it the word length from the previous call -1.  Each time
    through it checks the characters on each end of the string

    The first IF checks to see if we have gone through at least half of the
    characters yet. EX: for a 9 letter word we only need to
    compare 4 characters so the function would return at
    9/(9-4)= 1.8 is < 2 so return true.  This seems to work or at least
    I haven't found a word it doesn't work on.

   */

   if(word.length()/(word.length()-word_length+1) < 2){ // add one so we don't get undefined int/0
    return true;
   }
   if(word[word.length()-word_length] == word[word_length-1]){ //compare the two characters
        return is_pal(word, --word_length);
    }
    else{
        return false;
    }
}

int add_it (int first, int second){

    // iterate from 0 to second. adding 1 to the first
    // int each time through.
    int result = first;
    for(int current = 0; current < second; ++current){
        result++;
    }
    return result;
}

int add_rec(int first, int second){

    // recursivly add two numbers
    //  iterate by decreasing second
    // by one each time through and adding one
    // to first each time.  return first when
    // second is less than or equal to zero.

    if(second <= 0){
        return first;
    }
    else{
    return add_rec(++first, --second);
    }
}

int mult_rec(int first, int second, int current){
    /*
    recursivly mutliply two numbers.  The function uses the first
    integer, and decreses the second by one, then adds current to first
    through each call. Once second has decreased to less than or zero
    return current.
    */
    if(second <= 0){
        return current;
    }
    else{
    return mult_rec(first, --second, current+=first);
    }
}

int mult_it(int first, int second){
    /*
    Multiply two numbers by iterating. Each time
    through untill current < second, add first to
    the result.  Once the stop condition is met then
    return result.
    */
    int result = first;

    for(int current = 1; current < second; ++current){
        result += first;
    }
    return result;
}
