/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 Lab3 Repetition
** Input: 1, or -1
** Output: You squash a bug if 1 is entered, quit if -1 is entered
******************************************************/

#include <iostream>

// using cout, cin, and endl, so we can drop the std:: part
using std::cout;
using std::cin;
using std::endl;

int main() {

    int input = -1;
    // START with 99 bugs and decrease by 1 each time through the loop.  Stopping when verse = 1
    for ( int verse = 99; verse > 0; --verse) {
        // explain the input that we want to see
        cout << "what would you like to do today?" << endl;
        cout << "[1] Sting \"There are " << verse << " bugs reported to squash!" << endl;
        cout << "[-1] Quit this nonsense!" << endl;
        cin >> input;

        // Do stuff based on input
        if (input == 1) {
            cout << "Oh! You squashed a bug" << endl;
        }

        else if (input == -1) {
            cout << "You quit the game" << endl;
            return 0;
        }

    }
cout << " You Killed all the bugs!" << endl;
return 0;
}
