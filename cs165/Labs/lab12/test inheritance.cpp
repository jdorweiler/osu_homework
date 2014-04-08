#include <iostream>
#include <string>
#include <boost/random.hpp>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;

    class vehicle{

        public:
            vehicle(){};
            ~vehicle(){};

            virtual const string& getName(){}

            virtual void setName(const string& n){}

            friend std::ostream& operator <<(std::ostream& outs, vehicle &v){
            outs << v.getName();
            return outs;
            }

       protected:
           string name;

    };

    class car : public vehicle{

        public:

            car(){
                this->name = "default name";
            }

            void setName(const string& n){
                this->name = n;
            }

            const string& getName(){
                return this->name;
            }
};

typedef std::shared_ptr<vehicle> vehicle_ptr;

int main(){
       std::vector<vehicle_ptr> vehicleLot;

       vehicleLot.push_back(std::shared_ptr<car>(new car));

       cout << vehicleLot[0]->getName() << endl;

       vehicleLot[0]->setName("new name"); // this gives a seg fault

       cout << vehicleLot[0]->getName() << endl;

}
