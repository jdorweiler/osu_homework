/******************************************************
** Author: Jason Dorweiler
** Date: 11-22-13
** Description: CS165 Assignment 7
** compile with -std=c++0x
** Input: ./histogramPt1 then follow prompts
** Output:
How many dice do you have? 3
How many sides does die #1 have? 5
How many sides does die #2 have? 2
How many sides does die #3 have? 8
How many times do you want to roll the dice? 1234
 13-|
 12-|                $  $  $
 11-|                $  $  $
 10-|                $  $  $  $
 9 -|                $  $  $  $  $
 8 -|             $  $  $  $  $  $
 7 -|             $  $  $  $  $  $
 6 -|          $  $  $  $  $  $  $
 5 -|          $  $  $  $  $  $  $  $
 4 -|       $  $  $  $  $  $  $  $  $
 3 -|    $  $  $  $  $  $  $  $  $  $
 2 -|    $  $  $  $  $  $  $  $  $  $
 1 -|    $  $  $  $  $  $  $  $  $  $  $
     ---------------------------------------------
      3  4  5  6  7  8  9  10 11 12 13 14 15
********************************************************/
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <boost/random.hpp>
#include <string>
#include "limits.h"

// Seed PRNG
boost::mt19937 gen(time(NULL));

class  die{
    /*
    * The die class represents a single die with a set number
    * of sides.  Member functions to get the number of sides
    * and to roll the die.
    */

    public:

        die(){                          //Default constructor
            this->sides = 0;
        }

        ~die(){};                       //Destructor

        die(int s){                     //Constructor that sets the number of sides
            this->sides = s;
        }

        int getSides(){                  //return the number of sides
           return this->sides;
        }

        int rollDie(){                  //Roll the die and return a random in
                                        //based on the number of sides.
            int value;
            /*
            * set the uniform distribution from 1 to the number of sides
            * generate a random number in that range and return it.
            */
            boost::uniform_int<> dist(1,sides);
            boost::variate_generator<boost::mt19937&,
                boost::uniform_int<> > rng(gen, dist);

            value = rng();
            return value;
        }


    private:

        int sides;
};

void makeColors(std::map<int, std::string> &colors, int totalSides); // this function stores the color excape strings in a vector

void print_histogram(std::map<int, int> data,   // funciton that prints out a histogram to the screen
                     std::map<int, std::string> &colors,
                     int totalSides,
                     int rolls);

void getInput(std::vector<die> &dice, int &totalSides, int &rolls);      // get input from the user
int checkInput(int input);

template <class T1, class T2>
void roll(std::vector<T1> &dice, std::map<T2,T2> &hist, T2 rolls){
    /*
    * First off the templating is mostly just for fun to try it out.
    * I can't really see this working with other data types.
    *
    * The function loops over the number of rolls and then through
    * the number of dice.  Each time calling the rollDie function
    * for that particular die.  This returns a random int in the
    * range of 1 to numSides for that die.  Doing this allows for
    * dice with different number of sides.
    *
    * After that it checks the histogram map for the key
    * if the key isnt in the map it add the key, sets to zero
    * then incriments by one. At the end this gives a map
    * of dice sums (keys) and the total number of times that
    * this sum was seen (value).
    */

    for(int j = 0; j < rolls; ++j){  //for number of rolls
        int value = 0;  // reset total to zero after each roll
        for(auto i = dice.begin(); i != dice.end(); ++i){

            value += i->rollDie(); //get the random num back for each die rolled
        }
        if(hist.find(value) == hist.end()){
            hist[value] = 0;
        }
        ++hist[value];
    }
}

int main(){

    int totalSides, rolls;

    std::map<int, std::string> colors;
    std::vector<die> dice;  // vector that holds an instance of the dice class in each spot
    std::map<int,int> hist; // this is a map that contains [total : number of times seen] for each roll

    getInput(dice, totalSides, rolls); //get user input
    makeColors(colors, totalSides);  // function that holds the ANSI excape strings

    roll(dice, hist, rolls); // roll some dice

    print_histogram(hist, colors, totalSides, rolls);

    return 0;

}
void makeColors(std::map<int, std::string> &colors, int totalSides){
    /*
    * This function builds ANSI color codes for printing in color
    * they are stored in a vector with once color per entry
    */
    for(int i = 0; i < totalSides; ++i){
        int colorCode = i%6+1;
        // static cast to long long so it works on flip
        colors[i] = "\033[0;4"+std::to_string(static_cast<long long>(colorCode))+"m";

    }
}

void getInput(std::vector<die> &dice, int &totalSides, int &rolls){
    /*
    * Get user input for the total number of dice, number of sices
    * on each specific die and the total number of rolls to do.
    */
    int numSides, numDice;

    std::cout << "How many dice do you have? ";
    std::cin >> numDice;

    while(!checkInput(numDice)){
        std::cout << "Please enter an integer" << std::endl;
        std::cout << "How many dice do you have? ";
        std::cin >> numDice;
    }

    for(int i = 0; i < numDice; ++i){
        std::cout << "How many sides does die #" << i+1 << " have? ";
        std::cin >> numSides;

        while(!checkInput(numSides)){
        std::cout << "Please enter an integer" << std::endl;
        std::cout << "How many sides does die #" << i+1 << " have? ";
        std::cin >> numSides;
    }
        dice.push_back(die(numSides));
        totalSides += numSides;
    }

    std::cout << "How many times do you want to roll the dice? ";
    std::cin >> rolls;

    while(!checkInput(rolls)){
        std::cout << "Please enter an integer" << std::endl;
        std::cout << "How many times do you want to roll the dice? ";
        std::cin >> rolls;
    }
}

int checkInput(int input){
    // check input
    if(!std::cin || input < 1){
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        return 0;
    }
    return 1;
}
void print_histogram(std::map<int, int> data,
                     std::map<int, std::string> &colors,
                     int totalSides,
                     int rolls)
{
    /*
    * A good bit of this is borrowed from the code posted on blackboard
    * http://classes.engr.oregonstate.edu/~jessjo/CS162/lectures/histogram.cpp.
    * With comments and changes on my part to add colors and a y-axis.
    */
	int num_stars = 100;

	// 2d matrix to hold bool for each spot to print a block
	std::vector<std::vector<bool> > histogram;

	// highest percent
	int max = 0;

    // normalize to a percentage for each total
    // and get the max percent seen
	for(auto i = data.begin(); i != data.end(); ++i){
		int count = i->second * num_stars / rolls;

		//store the max percent
		max = std::max(max, count);

		//fill each row of the 2d matrix, this makes a horizontal histogram
		std::vector<bool> row;
		for(int j = 0; j < count; ++j) row.insert(row.begin(), true);
		histogram.push_back(row);
	}

    // fill the remaining matrix with 0s
	for(auto i = histogram.begin(); i != histogram.end(); ++i){
		for(int j = i->size(); j <= max; ++j){
            i->insert(i->begin(), false);
		}
	}

    //Print out the colored blocks level by level starting from the top
    // by checking histogram[j][i]
	for(int i = 0; i < max; ++i){
	    std::cout << " " << max-i << ((max-i < 10) ? " -|":"-|");
	    // for each level
		for (int j = 0; j < histogram.size(); ++j){
		    // for each column
		    if(histogram[j][i]){
                std::cout << " " << colors[j] <<  "  \033[m";
		    }
		    else{
                std::cout << "   ";
		    }
		}
		std::cout << std::endl;
	}
    std::cout << "     ";

    // print out the x-axis bar
    for(int i = 0; i < totalSides; ++i){
        std::cout << "---";
    }
    std::cout << std::endl;
    std::cout << "     ";

    //print out the x-axis lables
	for(auto i = data.begin(); i != data.end(); ++i)
		std::cout << " " << i->first << ((i->first < 10) ? " ":"");
	std::cout << std::endl << "            Percent vs. Dice Total " << std::endl;


}
