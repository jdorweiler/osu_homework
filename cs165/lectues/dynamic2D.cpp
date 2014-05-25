#include <iostream>
using namespace std;

void fill_array_of_arrays(int **arr, int height, int width);
void fill_array(int *arr, int width);
void print_array_of_arrays(int **arr, int height, int width);
void delete_array_of_arrays(int **arr, int height);
void setup_array(int **&arr, int height, int width);

int main(){

    //declare
    int height, width;
    int **grid;

    cout << "enter the integer height and width" << endl;
    cin >> height;
    cin >> width;

    setup_array(grid, height, width);

    fill_array_of_arrays(grid, height, width);

    print_array_of_arrays(grid, height, width);

    delete_array_of_arrays(grid, height);


return 0;
}

void setup_array(int **&arr, int height, int width){
    cout << "Grid being created with " << height << " rows." << endl;
    arr = new int*[height];

    for(int i = 0; i < height; i++){
        cout << "creating row # " << i << endl;
        arr[i] = new int[width];
    }
}
void fill_array_of_arrays(int **arr, int height, int width){
    for(int i =0; i < height; i++){
        cout << "you will be entering data for row " << i << endl;
        fill_array(arr[i], width);
    }
}

void fill_array(int *arr, int width){
    for(int i = 0; i < width; i++){
        cout << "please enter the value for element " << i << endl;
        cin >> arr[i];
    }
}

void print_array_of_arrays(int **arr, int height, int width){
    for(int i = 0; i < height; i++){
        cout << "row #" << i << "  [";
        for(int j = 0; j < width; j++){
            cout << arr[i][j];
            if(j % width != width -1 ){
                cout << " , ";
            }
        }
        cout << "]" << endl;
    }

}

void delete_array_of_arrays(int **arr, int height){
        for(int i = 0; i < height; i++){
            cout << "Now Deleteing Row #" << i << endl;
            delete arr[i];
        }
        cout << "Now Deleting Matrix" << endl;
        delete [] arr;
}
