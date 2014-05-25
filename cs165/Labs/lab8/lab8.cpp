/******************************************************
** Author: Jason Dorweiler
** Date: 10-23-13
** Description: CS165 lab 8
** Input: ./lab8 "Your input string to convert"
** Output:

*******************************************


          PigEnigma

   Pig Latin Cipher Generator

all lowercase no special characters!
*******************************************
You Entered: the white cat is fat

Generating ciphertext....
hetay hiteway atcay isway atfay

*******************************************************/
#include <iostream>
#include <cstring>
#include <stdio.h>

// array with vowels
char vowels[] = {'a','e','i','o','u'};

int isVowel(char*); // is the character a vowel
void startScreen(char **);
void PigEnigma(char **); // Pig latin generator function

using namespace std;
int main(int argc, char *argv[]){

    // print start screen send argv pointer to print message back to user
    startScreen(argv);

    // run pig latin converter function
    PigEnigma(argv);

return 0;

}

void PigEnigma(char *argv[]){
    /*
    Pig latin generator.
    1. loop over the number of characters in the argv array
    2. After that there is a series of logical checks and flags tha get set.
    3. Check to current char to see if it is a vowel. store bool in the type variable
    4. Check if type is true and the searching for space (space) flag is not set --This char is a vowel
    5. Check if not type and the space flag is not set -- this char is a consonant
    6. Then a funciton checks for spaces.  It prints out the pig latin chars based on what flags were set and resets them
    */
    char *charptr; // pointer to the current character
    bool space = false; // searching for a " " space flag
    bool isConsonant = false; //
    bool isVowelchar;
    char consonant; // store the consonant that is found for printing later
    char endChar = ' ';
    int type; // type of the character, vowel or consonant.

    for(int i = 0; i <= strlen(argv[1]); i++){

        //Check to see if we are at the end and add a space to properly print the last word
        // otherwise just set the charptr to the address of argv character.
        if(i == strlen(argv[1])){
            charptr = &endChar;
        }
        else{
        charptr = &argv[1][i];
        }

        // get the type of charater from isVowel() returns 1 for true, 0 for false
        type = isVowel(charptr);

        // Check to see if we have a vowel and are not looking for a space. if true
        // set space and isVowelchar flags to true
        if(type && !space){
            space = true;
            isVowelchar = true;
        }

        // Check to see if we don't have a vowel (consonant) and not looking for a space
        // set space and isConsonant flags to true.  Continue to stop from printing out
        // leading consonant character
        if(!type && !space){
            consonant = *charptr;
            space = true;
            isConsonant = true;
            continue;
        }

        // Check to see if we have a space.  Set flag to false
        if(*charptr == ' '){
            space = false;
            // check to see if isConsonant flag is true
            // print out "ay" and reset flag
            if(isConsonant){
            cout << consonant << "ay";
            isConsonant = false;
            }
            // check isVowelchar flag, print "way" and reset flag
            if(isVowelchar){
            cout << "way";
            isVowelchar = false;

            }
        }
        // print out the character
        cout << *charptr;
    }
cout << endl;
cout << endl;
}

int isVowel(char *n){
    //return 0 for a vowel and 1 for a consonant
    for(int i = 0; i < sizeof(vowels)/sizeof(char); i++){
        if(*n == vowels[i]){
            return 1;
            }
        }
    return 0;
}

void startScreen(char *argv[]){
cout << endl;
cout << "*******************************************" << endl;
cout << endl;
cout << endl;
cout << "          PigEnigma           " << endl;
cout << endl;
cout << "   Pig Latin Cipher Generator " << endl;
cout << endl;
cout << "all lowercase no special characters!" << endl;
cout << "*******************************************" << endl;
cout << "You Entered: " << argv[1] << endl;
cout << endl;
cout << "Generating ciphertext...." << endl;

}
