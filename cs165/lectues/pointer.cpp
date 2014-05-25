
#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b){
    cout << a << endl;
    cout << "1" << endl;
    int temp = a;
    a = b;
    b = temp;
}

void swap(int *a, int *b){
    cout << "2" << endl;
    int temp  = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char **argv){

    int *a = NULL;
    int *c = NULL;

    int b = 7;

    a = &b;

    cout << "set a to point to the address of b" << endl;

    cout << "a = "<< *a << " " << "b= "<< b << endl;

    b = 9;

    cout << "change the value of b to 9" << endl;

    cout << "a = "<< *a << " " << "b= "<< b << endl;

    int d = 8;

    c = &d;

    swap(*a, *c);

     cout << "a = "<< *a << " " << "c= "<< *c << endl;

    return 0;
}
