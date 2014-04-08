

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ios;
using std::stringstream;
using std::ifstream;
using std::map;

int main(int argc, char **argv){

        // file with the word list
    string filename = "words.txt";

    ifstream ifs(filename.c_str(), ios::app);

    map<char, int> hist;

    string input;

    while(ifs >> input){

        input.erase(input.begin());
        input.erase(input.end()-1);

        if(hist.find(input.front()) == hist.end()){
            hist[input.front()] = 0;
        }
        ++hist[input.front()];

    }

    for(auto i = hist.begin(); i != hist.end(); ++i){
        cout << i->first << " : " << i->second << endl;
    }

    std::sort(hist.begin(), hist.end());

    return 0;

}
