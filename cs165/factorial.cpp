// calculates the factorial of a number

#include <iostream>

using namespace std;

double factorial(int);

int main(){
    int number = 0;

    cout << "Enter a number to calculate the factorial of ";
    cin >> number;
    cout << endl;

    number = factorial(number);

    cout << number;

    return 0;
}

double factorial(int number){

    if (number <= 1){
        return 1;
    }
    else{
        return number * factorial(number -1);
    }
}
