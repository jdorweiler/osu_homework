#include <vector>
#include <iostream>

int main(void) {
    std::vector< std::vector<int> > v;
    v.push_back(17);
    v.push_back(12);
    v.push_back(23);
    v.push_back(42);
    for ( auto &i : v ) {
        std::cout << i << std::endl;
    }
    return 0;
}
