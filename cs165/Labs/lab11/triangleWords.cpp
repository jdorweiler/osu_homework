/******************************************************
** Author: Jason Dorweiler
** Date: 10-25-13
** Description: CS165 lab 11
** Input: compile with g++ -std=c++0x triangleWords.cpp -o triangle

./triangle

** Output:See below. The program also generates a triangleWords.txt file.
Words		Sum
A              01
ABILITY        078
ABOVE          045
ACCOMPANY      091
ACHIEVEMENT    0105
.
.
.
.
WHILST         091
WIDELY         078
WOMAN          066
The total number to triangle words in the list is: 162
**************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ios;
using std::stringstream;
using std::ifstream;

void getWords(ifstream &ifs, vector<string> &words);  //function that reads in the words from a text file and stores in a vector
void printResult(vector<string> &words, vector<int> &sums); // print out the vector
void search(ofstream &ofs, vector<string> &words, vector<string> &triWords, vector<int> &triNum, vector<int> &sums); // main search function that finds the triangle words
void createTri(vector<int> &triNum); // function that calculates the triangle numbers
bool checkSum(int sum, vector<int> &triNum); // function that checks the sume of the characters in the word

int main(int argc, char **argv){

    // create a vector. one word per line.
    vector<string> words;

    // vector for the triangle words
    vector<string> triWords;

    // vector for the calculated triangle numbers
    vector<int> triNum;

    // vector for the sum of each triangle word
    vector<int> triSum;

    // file with the word list
    string filename = "words.txt";

    // input and output file streams
    ifstream ifs(filename.c_str(), ios::app);
    ofstream ofs("triangleWords.txt", ios::app);

    // call funciton to create the list of triangle numbers
    createTri(triNum);

    // read in the words from the file into a vector
    getWords(ifs, words);

    // search words, add hits to triWord vector and print to output file
    search(ofs, words, triWords, triNum, triSum);


    printResult(triWords, triSum);

    return 0;

}
void createTri(vector<int> &triNum){
    /*
    * This function calculates the values for the triangle numbers
    * and stores them back in the triNum vector
    */
    for(int i = 1; i < 20; i++){
        triNum.push_back((i*(i+1)/2));
    }
}

bool checkSum(int sum, vector<int> &triNum){
    /*
    *   Function that takes the integer sum calculated by the search funciton
    *   it loops over the triNum vector and if the sum is in the calculated
    *   tri numbers it returns true, otherwise the word is not triangle and
    *   return false.
    */
    for(auto i = triNum.begin(); i != triNum.end(); i++){
        if(sum == *i){
            return true;
        }
    }
    return false;
}

void search(ofstream &ofs, vector<string> &words, vector<string> &triWords, vector<int> &triNum, vector<int> &sums){
    /*
    *   The main search function, takes the output stream, word list, empty triangle word list, list of
    *   triangle number, and in empty vector for the sums.
    *   Loop over the words in the word list, and characters in each word.  Add to the sum total and
    *   pass the sum to the checkSum funciton (returns bool).  Store the word in the triWords vector
    *   if it returns true.  Print to the output file stream.
    */
    int result;

    cout << std::left << "Words" << '\t' << '\t' << "Sum" << endl;
    for(auto i = words.begin(); i != words.end(); i++){ //loop over each line in the vector
        int sum = 0;

        for(auto j = i->begin(); j != i->end(); j++ ){ // loop over each character in the word
                sum += (int)*j-64; // convert to int

            }

        if(checkSum(sum, triNum)){ // check to see if it is a tri word, get a bool back
            triWords.push_back(*i); //put word to list of tri words
            sums.push_back(sum);    // store the sum
            ofs << *i << " " << sum << endl; // print to a file
        }
    }
}

void printResult(vector<string> &words, vector<int> &sums){
    /*
    *   Function that prints out the vectors
    */
    for(int i = 0; i < words.size(); ++i){
        cout << std::left << words[i] << cout.width(15) << sums[i] << endl;
    }
    cout << "The total number to triangle words in the list is: " << words.size() << endl;
}
void getWords(ifstream &ifs, vector<string> &words){
    /*
    *   Takes the input file stream and an empty vector to store the words in.
    *   Read each line in the file untill the end. Erase the quotes from the
    *   start and end of each word. Send the input to a stringstream
    *   and push back to the word list vector.
    */

    string input; // string to store the imput from ifs
    string v1; // temp string to store the chars from string stream

    while(getline(ifs, input)){
        string v;
        stringstream ss;

        input.erase(input.begin());
        input.erase(input.end()-1);

        ss << input; // word without quotes sent to string stream

        while(ss >> v1){ // send the string stream word to v1 and push back to the vector
            v = v1;
        }
        words.push_back(v);
    }

}
