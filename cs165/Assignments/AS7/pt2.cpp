/******************************************************
** Author: Jason Dorweiler
** Date: 11-22-13
** Description: CS165 Assignment 7
** compile with -std=c++0x
** Input: ./histogramPt1 then follow prompts
** Output:
How many dice do you have? 3
How many sides do they have? 7
How many times do you want to roll the dice? 100

                         *        *
                         *        *
                         *        *
                         *        *
                         *     *  *
                         *     *  *
                         *     *  *
                   *  *  *     *  *
                   *  *  *     *  *
          *     *  *  *  *     *  *     *
          *     *  *  *  *     *  *     *
    *     *  *  *  *  *  *  *  *  *     *
    *     *  *  *  *  *  *  *  *  *  *  *
    *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21
********************************************************/
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>


#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#endif

#if ((defined __GNUC__ && GCC_VERSION >= 40601) || (defined _MSC_VER  && _MSC_VER >= 1700))

#include <random> //C++11 (msvc/g++ >= 4.6.1)

#else //C++98 + boost

#include <boost/random.hpp>
#include <boost/version.hpp>

#endif


void getInput(int &Sides, int &rolls, int &numSides);      // get input from the user

//print a "normal" orientation histogram -- much more complicated than rotated
void print_histogram(std::map<int, int> data)
{
	int num_trials = 0;
	int num_stars = 100;
	std::vector<std::vector<bool> > histogram;
	int max = 0;

	for(auto i = data.begin(); i != data.end(); ++i) num_trials += i->second;

	for(auto i = data.begin(); i != data.end(); ++i){
		int count = i->second * num_stars / num_trials;
		max = std::max(max, count);
		std::vector<bool> row;
		for(int j = 0; j < count; ++j) row.insert(row.begin(), true);
		histogram.push_back(row);
	}

	for(auto i = histogram.begin(); i != histogram.end(); ++i){
		for(int j = i->size(); j <= max; ++j) i->insert(i->begin(), false);
	}


	for(int i = 0; i < max; ++i){
		for (int j = 0; j < histogram.size(); ++j){
			std::cout << ((histogram[j][i]) ? " * ":"   ");
		}
		std::cout << std::endl;
	}

	for(auto i = data.begin(); i != data.end(); ++i)
		std::cout << " " << i->first << ((i->first < 10) ? " ":"");
	std::cout << std::endl;

}

int main(int argc, char **argv)
{

	int value;
	int numDice;
	int numSides;
	int num_rolls;

	getInput(numDice, num_rolls, numSides);

#if ((defined __GNUC__ && GCC_VERSION >= 40601) || (defined _MSC_VER  && _MSC_VER >= 1700))

	//C++11 way (works in VS2012, g++ >= 4.6.1):
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(1,numSides);
	auto die = std::bind ( distribution, generator );

#elif (defined BOOST_VERSION && BOOST_VERSION < 104900)

	//boost way, prior to C++11 (works everywhere boost is installed, though this is boost < 1.49)
	boost::mt19937 rng;
	boost::uniform_int<> six(1,numSides);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, six);

#else

	//boost way, 1.49+
	boost::random::mt19937 rng;
	boost::random::uniform_int<> six(1,numSides);
	boost::random::variate_generator<boost::random::mt19937&, boost::random::uniform_int<> > die(rng, six);

#endif


	std::map<int, int> dice;


	for(int i = 0; i < num_rolls; ++i){
	    value = 0;
		for(int j = 0; j < numDice; ++j){
            value += die();
		}
		if(dice.find(value) == dice.end())   //if we haven't already rolled it...
			dice[value] = 1;                 //...add it to the map with a value of 1...
		else
			dice[value]++;                   //...otherwise increment it
	}


	print_histogram(dice);

	return 0;
}

void getInput(int &numDice, int &rolls, int &numSides){
    /*
    * Function added to get the number of dice, sides and
    * number of rolls from the user.
    */

    std::cout << "How many dice do you have? ";
    std::cin >> numDice;

    std::cout << "How many sides do they have? ";
    std::cin >> numSides;

    std::cout << "How many times do you want to roll the dice? ";
    std::cin >> rolls;
}
