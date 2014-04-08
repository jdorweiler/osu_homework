#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>

int main(int argc, char **argv){

    std::vector<std::vector<double> > matrix;

    double v1, v2, v3, v4;

    std::string input;

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
        std::vector<double> v;
        v.push_back(v1);
        v.push_back(v2);
        v.push_back(v3);
        v.push_back(v4);
        matrix.push_back(v);
    }

//    std::cout.setf(std::ios::scientific);
//    std::cout.setf(std::ios::showpoint);
//    std::cout.setf(std::ios::left);
//    std::cout.width(10);

        for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; j++){
            std::cout.width(10);
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::stringstream ss;
    double out;
//
//    ss << 1 << 2 << '.' << 7 << 2;
//    ss >> out;
//
//    std::cout << out << std::endl;

    ifs.close();
    ifs.open("input.txt");
    std::getline(ifs, input);

    ss << input

    return 0;
}
