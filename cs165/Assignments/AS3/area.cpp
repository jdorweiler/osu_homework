/******************************************************
** Author: Jason Dorweiler
** Date: 10-17-13
** Description: CS165 Assignment 3
** Input: The function number to calculate the area of,
          the bounds of the integral and the number of
          slices to use.
** Output:
**** Integral Calculator ****

     [1]  2x^2 + x^3 - 10x + 2
     [2]  6x^2 - X + 10
     [3]  5x + 3
     [4]  2x^3 + 120
     [5]  2x^2

Enter your function choice: 1
Enter the x-axis start: 1
Enter the x-axis stop: 2
Enter the number of slices: 1000
The area under the curve is 11.7745

 Would you like to calculate another?, [0] NO, [1] Yes
********************************************************/

#include <iostream>
#include <string>
#include <cmath> // for pow
#include <limits.h> // for cin error checking

using namespace std;

// function protoypes
void startScreen(); // prints input function choices
float get_float(string); // print out a string and get a float from the user
float check_valid_input(float, float, float); // check to see if a number is in between to others
float calc_rect_area(float, float); // calculate the area of a rectangle
float fun_funcs(int); // integrates the area under the curve of the chosen funciton

float f1(float);
float f2(float);
float f3(float);
float f4(float);
float f5(float);

#define FUNC_LOW 1 // lowest function number f1
#define FUNC_HIGH 5 //highes functino number f5

int main(){
    int replay = 1; // set to 1 for first loop. ask user if they want to continue after the first.

    while(replay){

        startScreen(); // print out start screen with user input choices
        int func = 0; // function number to calculate

        // get function number from the user, calculate the area with fun_funcs and see if
        // there is another calculation to do
        func = get_float("Enter your function choice: ");
        cout << "The area under the curve is " << fun_funcs(func) << endl;
        cout << endl;
        cout << " Would you like to calculate another?, [0] NO, [1] Yes ";
        cin >> replay;
        while(check_valid_input(replay, 0, 1) || !cin){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Enter O or 1" << endl;
            cin >> replay;
    }
        cout << endl;

    }

}
float fun_funcs(int func){
    /*
    `This functinon does some error checking on the input sent to it (func) to see
    if this is a valid function and does not cause a cin error.  After that it gets
    the bounds of the integral and the number of slices.  Then a switch calls the
    correct function and get the height of a rectangle back.  The area function is
    called using the calculated with. This loops over the number of slices and returns
    the total area.
    */
    float height, width, start, stop;
    int slices;
    double total = 0.0;

    //input error checking, call check valid input for funciton range.
    while(check_valid_input(func, FUNC_LOW, FUNC_HIGH) || !cin){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "That is not a valid function.  Please re-enter.." << endl;
        cin >> func;
    }

    // get integral bounds, slices
    start = get_float("Enter the x-axis start: ");
    stop = get_float("Enter the x-axis stop: ");
    slices = get_float("Enter the number of slices: ");

    // calculate width (dx)
    width = (stop - start)/slices;
   // cout << "width is " << width << " toatl is " << total << endl;

    // loop over the number of slices.  Get the height from the function, calculate
    // the area and add to the total.
    for(int i = 0; i < slices; i++){
        switch(func){
            case 1: height = f1(start+i*width);
                   // cout << "i*width" << i*width << "height " << height << endl;
                     total += calc_rect_area(width, height);
                     break;
            case 2: height = f2(start+i*width);
                     total += calc_rect_area(width, height);
                     break;
            case 3: height = f3(start+i*width);
                     total += calc_rect_area(width, height);
                     break;
            case 4: height = f4(start+i*width);
                     total += calc_rect_area(width, height);
                     break;
            case 5: height = f5(start+i*width);
                     total += calc_rect_area(width, height);
                     break;
        }
    }
return total;
}
// Math Functions //
float f1(float x){
    return 2*pow(x,5)+pow(x,3)-10*x+2;
}

float f2(float x){
    return 6*pow(x,2)-x+10;
}

float f3(float x){
    return 5*x+3;
}

float f4(float x){
    return 2*pow(x,3)+120;
}

float f5(float x){
    return 2*pow(x,2);
}

float get_float(string message){
    // get a string message from the user and
    // return a float that is entered.
    float user_val = 0.0;
    cout << message;
    cin >> user_val;
    while(!cin){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "That is not a valid input.. please re-enter ";
        cin >> user_val;
    }

    return user_val;
}

float check_valid_input(float n1, float n2, float n3){
    // takes three numbers and returns the first if it is between the
    // second and third numbers.
    if(n1 <= n3 && n1 >= n2){
        return 0;
    }
    else{
        return 1;
    }
}

float calc_rect_area(float width, float height){
    return width*height;
}

void startScreen(){
cout << " *******************************************" << endl;
cout << " *******      Integral Calculator    *******" << endl;
cout << " *******************************************" << endl;
cout << " *******  [1]  2x^5 + x^3 - 10x + 2  ******* " << endl;
cout << " *******  [2]  6x^2 - X + 10         ******* " << endl;
cout << " *******  [3]  5x + 3                ******* " << endl;
cout << " *******  [4]  2x^3 + 120            ******* " << endl;
cout << " *******  [5]  2x^2                  ******* " << endl;
cout << " *******************************************" << endl;

}

