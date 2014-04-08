#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

int main(){

    std::string letters = "aabbcc";

    std::cout << letters.at[0];
    std::map<int, int> database;
	std::vector<int> numbers;
    for(int i = 0; i < 100; i++){
        numbers.push_back(i);
        std::cout << i;
    }

    for(auto j = numbers.begin(); j != number.end(); j++){
        int index;
        index = database.find(j);
        if(index){
            database.find(j)->second++;
        }
        else{
            database.insert(j);
            database[j]->second = 0;
        }
    }

    for(auto k = letters.begin(); k != letters.end(); k++){
        char L1, L2;
        int count = 0;

        L1 = *k;

        if(L2 != L1 && count == 0){
            L2 = L1;
            std::cout << L1;
            count++;
        }
        else if(L2 != L1 && count != 0){
            std::cout << count;
            count = 0;
        }
        else{
            count++;
        }

    }

return 0;
}
