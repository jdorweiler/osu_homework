
#include <iostream>
#include <cstdlib>
using namespace std;

struct multi_div_value{
    int mult;
    float div;
};


void setup_table(multi_div_value &table, int height, int width);


int main(int argc, char *argv[]){

    int height = atoi(argv[1]);
    int width = atoi(argv[2]);
    multi_div_value table[height*width];
    setup_table(*table, height, width);


return 0;
}

void setup_table(multi_div_value &table, int height, int width){
    cout << "Table being created with " << height << " rows." << endl;
    for(int i = 0; i < height; i++){
        cout << "creating row # " << i << endl;
    }
}


