#import <iostream>

using namespace std;

//void setup(int **array, int cols, int rows);  // this one causes a segfault
void setup(int ***array, int cols, int rows); // this one works just fine

int main(int argc, char **argv){
    cout << "enter array size colxrows" << endl;
    int cols, rows;
    cin >>cols;
    cin >> rows;
    int address;

    int **array;

    cout << "& " << &array << endl;

    cout << "*&" << *&array << endl;

    cout << "**&" << &&array << endl;
    // initalize array
    setup(&array, cols, rows );




return 0;
}

void setup(int ***array, int cols, int rows){

    *&array = new int*[rows];

    for(int i = 0; i < rows; i++){
        *array[i] = new int[cols];

        }
}



