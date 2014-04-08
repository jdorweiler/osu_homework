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

template <class T1, class T2>
void roll(std::vector<T1> &dice, std::map<T2,T2> &hist, T2 rolls){

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
//            boost::uniform_int<> dist(1,sides);
//            boost::variate_generator<boost::mt19937&,
//                boost::uniform_int<> > rng(gen, dist);

            #if ((defined __GNUC__ && GCC_VERSION >= 40601) || (defined _MSC_VER  && _MSC_VER >= 1700))
                       std::cout << " one" << std::endl;
                //C++11 way (works in VS2012, g++ >= 4.6.1):
                std::mt19937 generator(time(NULL));
                std::uniform_int_distribution<int> distribution(1,sides);
                auto rng = std::bind ( distribution, generator );

            #elif (defined BOOST_VERSION && BOOST_VERSION < 104900)
                        std::cout << "two" << std::endl;
                //boost way, prior to C++11 (works everywhere boost is installed, though this is boost < 1.49)
                boost::mt19937 gen(time(NULL));
                boost::uniform_int<> six(1,sides);
                boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rng(gen, six);

            #else
                                   std::cout << "three" << std::endl;
                //boost way, 1.49+
                boost::mt19937 gen(time(NULL));
                boost::uniform_int<> dist(1,sides);
                boost::variate_generator<boost::mt19937&,
                boost::uniform_int<> > rng(gen, dist);

            #endif

            value = rng();
            std::cout << value << " " << sides << std::endl;
            return value;
        }


    private:

        int sides;
};

void getInput(std::vector<die> &dice, int &totalSides, int &rolls);      // get input from the user

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

    int totalSides, rolls;

    std::vector<die> dice;  // vector that holds an instance of the dice class in each spot
    std::map<int,int> hist; // this is a map that contains [total : number of times seen] for each roll

    getInput(dice, totalSides, rolls);

    roll(dice, hist, rolls);

    print_histogram(hist);

    return 0;

}

void getInput(std::vector<die> &dice, int &totalSides, int &rolls){
    int numSides, numDice;

    std::cout << "How many dice do you have? ";
    std::cin >> numDice;

    for(int i = 0; i < numDice; ++i){
        std::cout << "How many sides does die #" << i+1 << " have? ";
        std::cin >> numSides;
        dice.push_back(die(numSides));
        totalSides += numSides;
    }

    std::cout << "How many times do you want to roll the dice? ";
    std::cin >> rolls;
}
