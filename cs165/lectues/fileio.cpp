#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char **argv){

    std::vector<std::vector<int> > matrix;

    int v1, v2, v3, v4;

    std::string filename = "file.txt";



    std::ofstream ofs(filename.c_str(), std::ios::app);

    std::ifstream ifs("input.txt");

    std::cout << "helo file" << std::endl;

    ofs << "hello file! line 2" << std::endl;

//    for(int i = 0; i < 4; ++i){
//        std::vector<int> v;
//        for(int j = 0; j < 4; j++){
//            ifs >> input;
//            v.push_back(input);
//        }
//        matrix.push_back(v);
//    }

    while(ifs >> v1 >> v2 >> v3 >> v4){
        std::vector<int> v;
        v.push_back(v1);
        v.push_back(v2);
        v.push_back(v3);
        v.push_back(v4);
        matrix.push_back(v);
    }
        for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; j++){
            std::cout<< matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
