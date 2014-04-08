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

	std::vector<int> v;

	std::map<std::string, int> m;

	std::string key;

	key = "one";
	m[key] = 1;

	for(auto i = m.begin(); i != m.end(); ++i){
		//i->first is key
		//i->second is value
		//iterator points to a pair<key, value>

		std::cout << "Key:" << i->first << " maps to value:" << i->second << std::endl;

	}

	std::map<std::string, std::map<int, std::map<int, std::string> > > day;

	day["july"][17][2013] = "Thursday";

	//here is where things get...complicated...
	//random number example, using both random numbers and maps (3 ways -- middle version works on flip and VM)

#if ((defined __GNUC__ && GCC_VERSION >= 40601) || (defined _MSC_VER  && _MSC_VER >= 1700))

	//C++11 way (works in VS2012, g++ >= 4.6.1):
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(1,6);
	auto die = std::bind ( distribution, generator );

#elif (defined BOOST_VERSION && BOOST_VERSION < 104900)

	//boost way, prior to C++11 (works everywhere boost is installed, though this is boost < 1.49)
	boost::mt19937 rng;
	boost::uniform_int<> six(1,6);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, six);

#else

	//boost way, 1.49+
	boost::random::mt19937 rng;
	boost::random::uniform_int<> six(1,6);
	boost::random::variate_generator<boost::random::mt19937&, boost::random::uniform_int<> > die(rng, six);

#endif
	//my apologies, but this was a rapidly changing part of the spec, hence the 3 different ways to do it...

	int value;
	std::map<int, int> dice;
	int num_rolls = 7487000 * 6;

	for(int i = 0; i < num_rolls; ++i){
		value = die() + die();
		if(dice.find(value) == dice.end())   //if we haven't already rolled it...
			dice[value] = 1;                 //...add it to the map with a value of 1...
		else
			dice[value]++;                   //...otherwise increment it
	}


	print_histogram(dice);

	return 0;
}
