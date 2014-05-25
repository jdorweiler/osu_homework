#include <iostream>     // std::cout
#include <algorithm>    // std::set_intersection, std::sort
#include <vector>       // std::vector

int main ()
{
  int first[] = {3,7,12,8,2,45,2,7}; // some ints in an array
  int second[] = {5,2,7,4,6,34,7,88}; // more ints in another array
  std::vector<int> v(10);  // vector of 10 0s
  std::vector<int>::iterator it;

  std::sort (first,first+8); // sort the first array
  std::sort (second,second+8); // sort the second array

  // find the intersection of the 8 elements in the two arrays
  it=std::set_intersection (first, first+8, second, second+8, v.begin());

  // print out the elements of the intersection
  std::cout << "Elements in the intersection stored in the vector" << std::endl;
  for(auto i = v.begin(); i != v.end(); ++i) std::cout << *i << " ";
  std::cout << std::endl;

  // resize the vector based on the number of elements
  // returned from set_intersection.
  std::cout <<  &*it << " - " << &*v.begin() << " = " << (it - v.begin()) << std::endl;
  v.resize(it-v.begin());

  std::cout << "The intersection has " << (v.size()) << " elements:\n";
  for (it=v.begin(); it!=v.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

      return 0;
}
