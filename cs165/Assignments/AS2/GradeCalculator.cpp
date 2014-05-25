/******************************************************
** Author: Jason Dorweiler
** Date: 10-10-13
** Description: CS165 programming assignment # 2
** Input: Number of exercises and the score/total for each.
** Output:
How many exercises will be entered?
2
Enter your score for exercise 1
99
Enter the total possible on exercise 1
100
Enter your score for exercise 2
98
Enter the total possible on exercise 2
100
Your score is 197 out of 200 possible points  or 0.985%

******************************************************/
// including the libraries to use
#include <iostream> // used for cout, cin
#include <limits.h> // for error checking code

using namespace std;

// forward declarations
int inputErrorChecker(int);

int main(){

    // setup variables that we are using
    int exercises = 0;
    int studentScore = 0;
    int total = 0;

    // get the total number of exercises to calculate
    cout << "How many exercises will be entered?" << endl;
    cin >> exercises;

    // send input to error checker. If no errors it will just return
    // the input unchanged.  Otherwise it asks the user to re-enter
    exercises = inputErrorChecker(exercises);

    // loop from one to the number of exercises
    for (int i = 1; i <= exercises; i++){

        // variables to hold the scores for each individual exercise/total
        int subScore = 0;
        int subTotal = 0;

        // get the score and add it to the studentScore
        cout << "Enter your score for exercise " << i << endl;
        cin >> subScore;

        // send input to error checker. If no errors it will just return
        // the input unchanged.  Otherwise it asks the user to re-enter
        subScore = inputErrorChecker(subScore);

        studentScore += subScore; // add to the overall score

        // get the total and add it to the overall total
        cout << "Enter the total possible on exercise " << i << endl;
        cin >> subTotal;

        // send input to error checker. If no errors it will just return
        // the input unchanged.  Otherwise it asks the user to re-enter
        subTotal= inputErrorChecker(subTotal);

         total += subTotal; // add to the overall total

    }
    //print out results.  Calculate the percent.
    cout << "Your score is " << studentScore << " out of " << total << " possible points " << " or " << (float)studentScore/total << "%" <<endl;

    return 0;
}

int inputErrorChecker(int inputVar){

    while(inputVar < 1 || !cin){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " *** That value is invalid, please enter an integer" << endl;
        cin >> inputVar;

    }

    return inputVar;
}
