#include <boost/foreach.hpp>
#include <iostream>

int main(int argc, char **argv)
{

    int array[5] = {1,2,3,4,5};

    int element;

    BOOST_FOREACH(element, array){
        std::cout << element << std::endl;
    }
}
