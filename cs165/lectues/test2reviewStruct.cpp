//test review.

#import <iostream>

using namespace std;

struct animals{
    string cat;
    string lost_cat = "mow";
    string dog = "woof";
};

int main(){
    animals cat;

    cat.cat = "meow";
    cout << cat.cat;
}

