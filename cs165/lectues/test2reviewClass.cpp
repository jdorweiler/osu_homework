//test review.

#import <iostream>

using namespace std;


namespace animals{

    class animal{

        public:

        animal(string name, string say);
        friend ostream& operator <<(ostream &outstream, const animal &a);

        private:

        string says;
        string name;


    };

    animal::animal(string n, string say){
        says = say;
        name = n;
    }

    ostream& operator <<(ostream &outstream, const animal &a){
        outstream << a.name << " says " << a.says;

        return outstream;
    }
}


void print(animals::animal &am);

int main(){

    animals::animal cat("icky", "meow");

    animals::animal dog("mika", "herp");

    print(cat);
    print(dog);


}

void print(animals::animal &am){
    cout << "the animal says " << am << endl;
}
