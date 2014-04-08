#include <boost/foreach.hpp>
#include <iostream>
#include <boost/circular_buffer.hpp>

int main(int argc, char **argv)
{
    boost::circular_buffer<int> buffer(4);
    int bufferVar;

    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(4);


    std::cout<<"Initial Buffer State:"<<std::endl;

    BOOST_FOREACH(bufferVar, buffer)
    {
      std::cout << bufferVar<< std::endl;
    }

    std::cout << std::endl;

    buffer.pop_front();

    std::cout<<"Removing an element from the front:"<<std::endl;

    BOOST_FOREACH(bufferVar, buffer)
    {
      std::cout << bufferVar<< std::endl;
    }

    std::cout << std::endl;

    buffer.push_back(7);

    std::cout<<"Adding new data:"<<std::endl;

    BOOST_FOREACH(bufferVar, buffer)
    {
      std::cout << bufferVar<< std::endl;
    }

        std::cout << std::endl;

    std::cout<<"Fill buffer with new data:"<<std::endl;

    buffer.push_back(8);
    buffer.push_back(8);
    buffer.push_back(8);
    buffer.push_back(8);


    BOOST_FOREACH(bufferVar, buffer)
    {
      std::cout << bufferVar<< std::endl;
    }


}
