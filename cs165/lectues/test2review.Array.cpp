#import <iostream>

using namespace std;

void print(int *array);
void add(int array[]);

int main(int argc, char **argv){

        int array[3] = {1,2,3};
        cout << "array at initialization " << &array << endl;

        cout << array[2] << endl;
        add(array);

        cout << array[2] << endl;

        add(array);

        cout << array[2] << endl;

 return 0;
}


void print(int *array){
            cout << "before declaring memory " << &array << endl;

                cout << " after declaring memory " << &array << endl;
}

void add(int array[]){
    cout << " start of add " << &array << endl;
    array[2] +=5;
                cout << "in adding function " << &array << endl;
}
