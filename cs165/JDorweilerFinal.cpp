/******************************************************
** Author: Jason Dorweiler
** Date: 12-6-13
** Description: CS165 final
** compile with -std=c++0x
** Input: ./final -filename
** Output: This program runs through three examples
**  for the use of binary/hex number, arrays, and
**  classes.  A list of requirements for the final
**  that were met is printed to the output file.
**
**  There are many calls to storeMap() throughout
**  the code.  These are use to store the requirement
**  and the approx line number where it was met.
**/

#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <climits>
#include <boost/random.hpp>
#include <tr1/memory>  // for shared pointers
#include <fstream>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;

/*
*   Inside of the Zoo namespace is the Animal class
*   This class contains all of the protected variables
*   for the animal subtypes.  It also uses an operator
*   overload for the ostream <<.  The overload calls
*   a virtual function inside of the animal class
*   which then gets passed by the magic of polymorphism
*   to the subclass print function.  This allows me to print
*   specific things for each animal. For example, Fish have
*   fins but none of the other animals do so there is no
*   point in printing out the number of fins that a bird
*   has.
*/
namespace Zoo{

    class Animal{

        public:

            Animal(){}; // default constructor
            virtual ~Animal(){}; // virtual destructor to work with subclasses

            virtual void print(std::ostream &outs) const = 0;

            // Get the type of animal. There could be one for each variable
            // but I'm only using this one.
            virtual const string getType(){
                return this->type;
            }

        protected:

            string name;
            string type;
            string habitat;
            int legs;
            int fins;
            string favFood;
            bool tail;

    };

        // ostream override call the print function from the subclass
        // and prints the returned ostream
        std::ostream& operator <<(std::ostream &outs, Animal &a){
            a.print(outs);
            return outs;
        }

    class Reptile : public Animal{

        public:

        Reptile(string name, string type, string habitat, int legs, string favFood){
            this->name = name;
            this->type = type;
            this->habitat = habitat;
            this->legs = legs;
            this->favFood = favFood;
        }

        virtual void print(std::ostream &outs) const {
            outs << "Name: " << name << endl
                 << "Favorite Food: " << favFood << endl
                 << "# of Legs: " << legs << endl
                 << "Habitat: " << habitat << endl;
        }

    };

    class Mammal : public Animal{

        public:

        Mammal(string name, string type, string habitat, int legs, string favFood){
            this->name = name;
            this->type = type;
            this->habitat = habitat;
            this->legs = legs;
            this->favFood = favFood;
        }

        virtual void print(std::ostream &outs) const {
            outs << "Name: " << name << endl
                 << "Favorite Food: " << favFood << endl
                 << "# of Legs: " << legs << endl
                 << "Habitat: " << habitat << endl;
        }

    };

    class Fish : public Animal{

        public:

        Fish(string name, string type, string habitat, int fins, string favFood){
            this->name = name;
            this->type = type;
            this->habitat = habitat;
            this->fins = fins;
            this->favFood = favFood;
        }

        virtual void print(std::ostream &outs) const {
            outs << "Name: " << name << endl
                 << "Favorite Food: " << favFood << endl
                 << "# of fins: " << fins << endl
                 << "Habitat: " << habitat << endl;
        }

    };

    class Amphibian : public Animal{

        public:

        Amphibian(string name, string type, string habitat, int legs, string favFood, bool tail){
            this->name = name;
            this->type = type;
            this->habitat = habitat;
            this->legs = legs;
            this->favFood = favFood;
            this->tail = tail;
        }

        virtual void print(std::ostream &outs) const {
            outs << "Name: " << name << endl
                 << "Favorite Food: " << favFood << endl
                 << "# of Legs: " << legs << endl
                 << "Habitat: " << habitat << endl
                 << "Tail: " << tail << endl;
        }

    };

    class Bird : public Animal{

        public:

        Bird(string name, string type, string habitat, int legs, string favFood){
            this->name = name;
            this->type = type;
            this->habitat = habitat;
            this->legs = legs;
            this->favFood = favFood;
        }

        virtual void print(std::ostream &outs) const {
            outs << "Name: " << name << endl
                 << "Favorite Food: " << favFood << endl
                 << "# of Legs: " << legs << endl
                 << "Habitat: " << habitat << endl;
        }

    };

}

using namespace Zoo;

typedef std::tr1::shared_ptr<Animal> AnimalPtr; // shared pointer to animal object
typedef std::map<int, string> Map; // map of key: integers, and Value: strings

void welcomeScreen();   // print the start screen
void continueOn();      // wait for Enter key to continue program
void getInput(int &n, string s, int max); // error check integer input
int getArgv(const int &argc,char **argv, string &filename); // get commandline input
void arrays(); // main program for array portion of the program
void printArray(int *array, int width); // recursively a print 1d array
void delete2Darray(int **arr, int height); // delete a 2d array
void setup_array(int **&arr, int height, int width); // fill array with random ints
void print2DArray(int **arr, int height, int width); // print 2d array
void calculator(); // main function for the binary and hex calculator
void runZoo(); // main function for the zoo class part of the program
void printVector(std::vector<AnimalPtr> &AnimalZoo, string &selection); // print out a vector
void storeMap(int num, string output, int line, int adj); // store the requirements in a map
void printOFS(ofstream &ofs, const string &filename); // print map to an output file

// map that holds the completed requirements for
// the final.  Global to avoid having to pass it
// to every single function.  Same for grade.
Map req;
int grade = 0;

int main(int argc, char **argv){


    string filename; // file name from argv

    if(getArgv(argc, argv, filename)) return 1; // check to see if we got a good file name

    ofstream ofs(filename, std::ios::app); // open the output file stream

    welcomeScreen(); // print the start screen

    continueOn(); // wait for Enter key

    cout << "*****************************************************" << endl;
    cout << "The first part of this program will work with binary" << endl
         << "hex and 2s complement number." << endl;

    calculator(); // run the calculator

    continueOn(); // wait for Enter key

    cout << "*****************************************************" << endl;
    cout << "The second part of this program will work with static," << endl
         << "dynamic arrays, and recursion" << endl << endl;

    arrays(); // run the array demo

    continueOn(); // wait for Enter key

    cout << "*****************************************************" << endl;
    cout << "The second part of this program will work with classes." << endl
         << "The Zoo namespace has an Animal class and subclasses." << endl
         << "there are 5 subclasses: mammal, reptile, fish, amphibian," << endl
         << "and bird. The Zoo has been pre-filled with animals." << endl;

    runZoo(); // run the zoo demo

    storeMap(19, "Generally uses functional decomposition ** kept Main() very short **", __LINE__, 0);

    printOFS(ofs, filename); // print the map to the output file

    ofs.close();

    return 0;
}
// print out the start screen
void welcomeScreen(){

    cout << endl
         << "CS165 Final, Jason Dorweiler" << endl
         << "** This is a self grading final **" << endl
         << "After the program finishes check the output file for" << endl
         << "for a list of requirements met and approximate" << endl
         << "line number in the code. If not the exact line at least in the" << endl
         << "function where the requrement was met." << endl << endl
         << "The program is in three parts:" << endl
         << "1.  Binary, Hex, and 2s complement calculations" << endl
         << "2.  Fun with dynamic and static arrays" << endl
         << "3.  Classes and inheritance - Zoo of animals" << endl;
}

// wait for the enter key
void continueOn(){
    cout << "Press ENTER to continue" << endl;
    cin.ignore(INT_MAX, '\n');
    for(int i = 0; i < 20; ++i){
        cout << endl;
    }
}

/*
*   Check to see if the file name was entered on the
*   command line.  Throw an error and exit the program
*   if no file was entered.  Otherwise, get the filename
*   for the output file stream to use.
*/
int getArgv(const int &argc,char **argv, string &filename){

    storeMap(29, "Uses at least one command line argument ** for the file name **", __LINE__, 0);
    storeMap(12, "Uses some form of conditional", __LINE__, 5);

    try{
        // First check to see if a filename was entered
        // then check for a '-' character.
        if(argc != 2 || argv[1][0] != '-'){
            throw 1;
        }

    }
    catch(int e){
        cout << endl;
        cout << "Program returned error: " << e << endl
             << "This program creates an output file and needs a name" << endl
             << "Correct Usage: ./final -OutputFileName" << endl << endl;
        return 1;
    }

    filename = argv[1]; // get the file name from argv
    filename.erase(filename.begin()); // strip off the "-"

    try{
        if(filename.length() < 1){
            throw 2;
        }
    }
    catch(int e){
        cout << endl;
        cout << "Program returned error: " << e << endl
             << "File name length needs to be greater than 0" << endl
             << "Correct Usage: ./final -OutputFileName" << endl << endl;
        return 1;
    }

    filename += ".txt"; // make it a .txt file

    storeMap(46, "Uses exceptions", __LINE__, -12);

    return 0;

}

void runZoo(){

    // Declare a vector of pointers to animal objects
    std::vector<AnimalPtr> AnimalZoo;

    storeMap(36, "Attempts to use a pointer to a class ** smart pointer to animal class **", __LINE__, -2);
    storeMap(37, "Uses its own namespace ** Animal class is in the Zoo namespace", __LINE__, 0);
    storeMap(39, "Uses at least one vector", __LINE__, -4);

    int tempNum; // temp number used for user input
    string selection; // type of animal to see
    int replay = 1; // to replay the selection screen

    // fill vector with animals
    AnimalZoo.push_back(std::tr1::shared_ptr<Mammal>(
        new Mammal("Cat", "mammal", "house", 4, "string cheese")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Mammal>(
        new Mammal("Wolf", "mammal", "wild", 4, "cats")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Mammal>(
        new Mammal("Fox", "mammal", "wild", 4, "mice")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Reptile>(
        new Reptile("Snake", "reptile", "tree", 4, "mice")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Amphibian>(
        new Amphibian("Salamander", "amphibian", "swamp", 4, "bugs", true)));

    AnimalZoo.push_back(std::tr1::shared_ptr<Reptile>(
        new Reptile("Gator", "reptile", "swamp", 4, "fish")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Fish>(
        new Fish("Lionfish", "fish", "salt water", 8, "small fish")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Fish>(
        new Fish("Shark", "fish", "salt water", 2, "seals")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Bird>(
        new Bird("Seagul", "bird", "Land", 2, "garbage")));

    AnimalZoo.push_back(std::tr1::shared_ptr<Amphibian>(
        new Amphibian("Frog", "amphibian", "fresh water", 4, "flys", false)));


    storeMap(32, "Defines at least one class ** Animal Class **", __LINE__, -3);

    while(replay){
        cout << "We have a zoo with 5 types of animals in it:" << endl
             << "[1] Mammals" << endl
             << "[2] Reptiles" << endl
             << "[3] Birds" << endl
             << "[4] Amphibians" << endl
             << "[5] Fish" << endl << endl
             << "Enter a Number to learn more about each: ";
        cin >> tempNum;
        cout << endl;

        // what type of animal does the user want to see
        // get the type from the number entered
        switch(tempNum){

            case(1):
                selection = "mammal";
                break;

            case(2):
                selection = "reptile";
                break;

            case(3):
                selection = "bird";
                break;

            case(4):
                selection = "amphibian";
                break;

            case(5):
                selection = "fish";
                break;

        }

        storeMap(23, "Uses at least one string variable", __LINE__, -5);

        printVector(AnimalZoo, selection); // print out the type

        cout << "Would you like to see another? [1] Yes, [0] No I'm done: " << endl;
        cin >> replay;
    }

}
/*
*   Print out the vector of pointers to animals based
*   on the type of animal requested.
*/
void printVector(std::vector<AnimalPtr> &v, string &selection){
        // loop over the vector
        for(auto i = v.begin(); i != v.end(); ++i){
            // get the type from the animal object
            if((*i)->getType() == selection){
                // print out the animal using the
                // subclass overlaoded ostream
                cout  << **i <<  endl;
            }
    }

    storeMap(20, "Demonstrates how scope of variables works ** vector declared in a functions an passed around by ref",
             __LINE__, -12);
    storeMap(22, "Demonstrates function overloading ** this line uses overloaded ostream **", __LINE__, -6);
    storeMap(33, "Uses at least one object ** Getting type from animal object **", __LINE__, -10);


}

/*
*   This is the main array part of the program.  It declares a static 1d array
*   fill it with random integers, gets user input which is used to a dynamic
*   make a dynamic 2d array
*/
void arrays(){

    int width = 5; // for static array
    int height;

    int *array = new int[width]; // pointer to an array

    storeMap(25, "Uses at least one one-dimensional array", __LINE__, -2);
    storeMap(27, "Uses at least one statically declared array", __LINE__, -3);

    for(int i = 0; i < width; ++i){
        array[i] = rand()%9-1;
    }

    cout << "A static array was declared, filled with random" << endl
         << "integers and printed with the recursive function" << endl << endl;

    cout << "The random static array of 5 integers is:" << endl;
    printArray(array, 5);
    cout << endl << endl;

    delete [] array;

    cout << "Lets make a dynamic 2d array" << endl;
    getInput(width, "enter the width from 1-9: ", 9);
    getInput(height, "enter the height from 1-9: ", 9);

    int **array2D;

    storeMap(26, "Uses at least one multi-dimensional array", __LINE__, -2);
    storeMap(28, "Uses at least one dynamically declared array", __LINE__, -3);

    setup_array(array2D, height, width);

    cout << endl << "Here is your random 2d dynamic array" << endl;

    print2DArray(array2D, height, width);

    cout << endl << endl;

    delete2Darray(array2D, height);

    cin.ignore();

}

/*
*  Sets up the 2d Array with a user defined height,
*  width, and fills with random number.
*/
void setup_array(int **&arr, int height, int width){

    storeMap(21, "Demonstrates the different ways to pass variables ** Array pointer passed by address** ",
             __LINE__, -3);

    arr = new int*[height];

    for(int i = 0; i < height; i++){
        arr[i] = new int[width];
        for(int j = 0; j < width; ++j){
            arr[i][j] = rand()%100-1;
        }
    }

}


/*
*   Print out the 2d Array
*/
void print2DArray(int **arr, int height, int width){

    // loop over the rows
    for(int i = 0; i < height; i++){
        cout << "[";

        // loop over the columns
        for(int j = 0; j < width; j++){
            cout << std::setw(2) << arr[i][j];

            // check to see if we are at the end of a row
            if(j % width != width -1 ){
                cout << " , ";
            }
        }
        cout << "]" << endl;
    }
}


/*
*   This is the recursive function used to print out
*   the 1d array
*/
void printArray(int *array, int width){
        if(width == 0){

            storeMap(24, "Uses some form of recursion ** printed from recursive array function **", 564, 0);

            return ;
        }
        else{
            // call print array again and decrease width
            printArray(array, --width);
        }
        cout << array[width] << " ";
}

/*
*   This function just deletes the 2d matrix
*/
void delete2Darray(int **arr, int height){
        for(int i = 0; i < height; i++){
            delete arr[i];
        }
        delete [] arr;
}

/*
*   Calculator part of the program.  This shows
*   the use of bit flags
*/
void calculator(){
    std::srand(time(0));

    int decNum;
    int randN;

    storeMap(6, "Uses variables in C++ ", __LINE__, -3);

    // get a decimal number from the user
    getInput(decNum, "Please enter an integer number from 1-255 (to keep bin numbers small): ", 255);
    cout << endl;

    /*
    * This part just shows the use of bitflags and converting between binary and hex
    * I included some print statements to show how the calculations work if done by
    * hand.
    */
    cout << "Lets convert the number to binary using 2^n for each bit. Ex:" << endl
         << "dec number 12 in binary is 1*8 + 1*4 +2*0+1*0 = 1100"<< endl
         << "Your number is " << decNum << " in binary is " << std::bitset<8>(decNum) << endl << endl

         << "Lets convert your number to hex. Ex: decimal number 100 is 0x64 in hex which is 6*16+4 = 100"
         << endl << "Your number in hex is " << std::hex << "0x" << decNum << std::dec << endl << endl;

    storeMap(2, "Demonstrates understanding of binary numbers", __LINE__, -6);
    storeMap(3, "Demonstrates understanding of hexadecimal numbers", __LINE__, -4);

    /*
    *   2s complement reserves the left most bit for the sign of the number.
    *   Here is an example of doing 2s complement by hand:
    *
    *   -6+3 = -3
    *
    *   1010 = -6 in 2s complement
    * + 0011 = 3
    * -----------
    *   1101 = -3 in 2s complement
    *
    */

    //generate a negative random number for 2s complement calculation
    randN = -rand()%9-1;

    storeMap(8, "Uses some form of arithmetic expression", __LINE__, -2);
    storeMap(15, "Uses a random number", __LINE__, -3);

    cout << "Lets do some 2s complement math with your number"
         << " and a random negative number (see comments for hand calculation)" << endl
         << decNum << " + " << randN << " = " << decNum+randN << endl
         << endl << std::bitset<8>(decNum) << " + " << std::bitset<8>(randN)
         << " = " << std::bitset<8>(decNum+(randN)) << endl
         << "*****************************************************" << endl;

    storeMap(4, "Demonstrates understanding of two's complement numbers", __LINE__, -4);
    storeMap(9, "Uses some form of simple output", __LINE__, -4);

    cin.ignore();
}

/*
*   function used to get and filter input from the
*   user.  Prints out a string passed to it.
*/
void getInput(int &n, string s, int max){
    // print the string and get input from the user
    cout << s;
    cin >> n;

    storeMap(10, "Uses some form of simple input", __LINE__, -2);

    //check the input and ask for it again if there is
    //a problem.  Using the OR operator to check if there
    // is a cin problem or n is greater than the max int.
    while(!cin || n > max || n < 0){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << s;
        cin >> n;
    }

    storeMap(5, "Uses some pre-defined macro from an existing include or library", __LINE__, -5);
    storeMap(7, "Uses some form of boolean expression", __LINE__, -8);
    storeMap(13, "Uses some form of logical or bitwise operator", __LINE__, -9);
    storeMap(14, "Uses at least one loop,", __LINE__, -10);
    storeMap(17, "Demonstrates some form of debugging tricks **This while loop filters bad user input **", __LINE__, -11);
    storeMap(18, "Uses at least one function that you define", 646, 0); // this is a given one
}

/*
*   The storeMap function stores the integer number for each requirement
*   for the final as the key and the string containing which requirement
*   was met and what line to find it on.
*/
void storeMap(int num,  string output, int line, int adj){
    // store in Key:num and Value: output + the line number
    // first check to see if the key is in the map
    // add the string it not, otherwise do nothing.
    if(req.find(num) == req.end()){
        // need to cast as long long to work on flip.  I guess it's an old compiler
        // error that got updated in newer versions.
        req[num] = output + " Line:  " + std::to_string(static_cast<long long>(line + adj));
        grade++;
    }
}

void printOFS(ofstream &ofs, const string &filename){

    // I dont want negative EC but if I do then
    // overflow to give me tons of EC ;)
    unsigned long extra_credit;

    // misc requirements that don't really have a line number to add
    // or can't be added in a logical area, i.e. inside of a class
    storeMap(40, "Defines classes covering the use of default constructors ** Animal subclasses use default constructors",
             __LINE__, 58);
    storeMap(41, "Demonstrates overloaded operators ** overloaded ostream in animal class **", 79, 0);
    storeMap(42, "Uses some form of file IO", __LINE__, 0);
    storeMap(43, "Uses other classes for some neat effects ** Used vectors, map, and shared_pointers **", 0, 0);
    storeMap(44, "Uses inheritance ** Animal sub-types inherit from the animal class **" , 0, 0);
    storeMap(45, "Uses polymorphism  ** virtual ostream and getType functions for the sub classes of animal", 57, 0);
    storeMap(16, "Demonstrates understanding of the three general error categories ** I think I covered this through error checking the file input and user input",0,0);
    storeMap(11, "Uses some form of type casting ** in storeMap function **", 683, 0);

    // loop over each key in the map and print to the output file
    for(auto i = req.begin(); i != req.end(); ++i){
        ofs << i->first << ". " << i->second << endl;
    }

    ofs << endl << "No. of Requirements Met: " << grade << "/45" << endl;
    cout << endl << "No. of Requirements Met: " << grade << "/45" << endl;

    cout << "Enter extra credit points: ";
    cin >> extra_credit;

    ofs << "Extra credit points: " << extra_credit << endl;
    cout << "Output file: " << filename << " has a detailed list of the requirements met" << endl;
}
