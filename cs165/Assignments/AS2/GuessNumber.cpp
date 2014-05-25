/******************************************************
** Author: Jason Dorweiler
** Date: 10-10-13
** Description: CS165 programming assignment # 2
** Input: For a human player, enter in the guess each rount
          For a computer player just enter in the secret number for it to guess
** Output:
****************************************
******* Guess the Number Game **********
****************************************
****************************************
******* [1]  You Guess a Number ********
****************************************
********[2]  Computer Guesses **********
****************************************
****************************************
2

Enter a Number from 1 to 50 for the Computer to Guess 34

The range is 1 to 50
Lives: 5
The computer guesses 25

Higher

The range is 26 to 50
Lives: 4
The computer guesses 38

Lower

The range is 26 to 37
Lives: 3
The computer guesses 31

Higher

The range is 32 to 37
Lives: 2
The computer guesses 34

*********************
***** Computer Wins!  *****
*********************
 Do You Want to Play Again?
[1] Yes
[0] No

******************************************************/
// including the libraries to use
#include <iostream> // used for cout, cin
#include <cstdlib> // used for rand and srand
#include <limits.h> // for INT_MAX to clear cin

//forward declarations
void startScreen();
void clearScreen();
void humanPlayer(); // game for human player making guesses
void computerPlayer(); // game for computer player making guesses
void restart();
int inputErrorChecker(int, int, int);

// globals
int runGame = 1; // what type of game is going to run human =1, computer = 2
int lives = 5;  // start with 5 lives
int randNumber = 0; // initialize random number
int gameMin = 1;    // set game limits
int gameMax = 50;

using namespace std;



int main(){

    srand(time(0)); // seed the PRNG

    // main loop running the game
    while(runGame){

        //display the start screen
        startScreen();
        // clear screen before the game
        clearScreen();

        // Human player
        if (runGame == 1){
            randNumber = rand()%gameMax + gameMin; // generate random number
            humanPlayer();
        }
        // computer player
        if (runGame == 2){
            computerPlayer();
        }
        //see if user wants to play again
        restart();
    }
    return 0;
}

void restart(){
    //check to see if the user wantes to play again
    // reset some of the global variables for the next game
    cout << " Do You Want to Play Again?" << endl;
    cout << "[1] Yes" << endl;
    cout << "[0] No" << endl;
    cin >> runGame;

    runGame = inputErrorChecker(0, 1, runGame);

    // Reset Globals
    lives = 5;
    gameMin = 1;
    gameMax = 50;
    return;
}

void computerPlayer(){
    // Enter in a number and the computer will make guesses by doign a binary search
    // The computer always guesses half of the range.  For a range from 1-50 a worse case
    // is when you pick 1 or 50.  For example  you pick 1, Computer will pic 25, 12, 6, 3, and then
    // be left to pick 1 or 2 with its' 5th life.

    // initialize the guess
    int guess = 0;

    // get the random number from the user
    cout << "Enter a Number from 1 to 50 for the Computer to Guess ";
    cin >> randNumber;

    // check for a number in the correct range
    randNumber = inputErrorChecker(gameMin, gameMax, randNumber);

    cout << endl;

    // run the computer game while there are still lives
    while(lives){
        // print out some helpful game stats
        cout << "The range is " << gameMin << " to " << gameMax << endl;
        cout << "Lives: " << lives << endl;

        //computer makes its' guess
        guess = (gameMax + gameMin)/2;
        cout << "The computer guesses " << guess << endl;
        cout << endl;

        // The next if-else statements check to see if the
        // number was higher, lower, or equal to the secret number
        if ( guess == randNumber){
            cout << "*********************" << endl;
            cout << "***** Computer Wins!  *****" << endl;
            cout << "*********************" << endl;
            return;
        }
        // if the guess was low
        if (guess > randNumber){
            cout << "Lower" << endl;
            gameMax = guess -1;
            lives--;
            cout << endl;
        }
        //if the guess was high
        else {
            cout << "Higher" << endl;
            gameMin = guess + 1;
            lives--;
            cout << endl;
        }
    }
    // print out result and return
    cout << "**** Computer Looses! ****";
    cout << " The number was " << randNumber << endl;
    return;

}

void humanPlayer(){

    // initialize the guess
    int guess = 0;

    // start human player game
    while(lives){

        // print out helpful game stats and get player's guess
        cout << "The range is " << gameMin << " to " << gameMax << endl;
        cout << "Lives: " << lives << endl;
        cout << "Enter Your Guess ";
        cin  >> guess;
        cout << endl;

        // check for input errors.  Guess should not cause cin errors and
        // be between 1 and 50
        guess = inputErrorChecker(1, 50, guess);

        // the following if-else statements check to see if the guess was
        // higher, lower, or equal to the secret number
        if ( guess == randNumber){
            cout << "*********************" << endl;
            cout << "***** You Win!  *****" << endl;
            cout << "*********************" << endl;
            return;
        }
        // if the guess was too low
        if (guess > randNumber){
            cout << "Lower" << endl;
            gameMax = guess -1;
            lives--;
            cout << endl;
        }
        // if the guess was too high
        else {
            cout << "Higher" << endl;
            gameMin = guess + 1;
            lives--;
            cout << endl;
        }
    }
    // return game result, and return from function
    cout << "**** You Lose! ****";
    cout << " The number was " << randNumber << endl;
    return;

}

void startScreen(){
    // Print out the start screen and get the choice of game type
    cout << "****************************************" << endl;
    cout << "******* Guess the Number Game **********" << endl;
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cout << "******* [1]  You Guess a Number ********" << endl;
    cout << "****************************************" << endl;
    cout << "********[2]  Computer Guesses **********" << endl;
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cin >> runGame;

    // check for input errors
    runGame = inputErrorChecker(1, 2, runGame);

    return;
}

void clearScreen(){
    // clear the screen before the game by printing blank lines
    for(int i = 0; i <= 20; i++){
        cout << endl;
    }
    return;
}

int inputErrorChecker(int min, int max, int input){
    // this function check for input errors.
    // the input has to be greater than min, less than max and
    // not cause a cin error.  The function just sends the number
    // back if all checks pass.
    while(input < min || input > max || !cin ){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Your input was outside of the allowed range " << min << " to " << max << endl;
        cout << "Please re-enter a valid input ";
        cin >> input;
    }
    return input;
}

