/******************************************************
** Author: Jason Dorweiler
** Date: 12-1-13
** Description: lab13
** compile with -std=c++0x
** Input: ./inheritance then follow prompts
** Output:
Enter the number of vehicles
Up to 10 max, or an error will be thrown
11
Error: 1
Number of vehicles is too high.. setting to max of 10
Initializing 10 random vehicles
Vehicle Type  Transport  Wheels  Doors  Price     Miles
Boat         | Water     | 0     | 0  | $28722   | 3639
Bike         | ground    | 2     | 0  | $656     | 375
Space Ship   | space     | 3     | 1  | $121435  | 3043596
Car          | ground    | 4     | 4  | $9506    | 12453
Bike         | ground    | 2     | 0  | $492     | 500
Bike         | ground    | 2     | 0  | $984     | 250
Bike         | ground    | 2     | 0  | $656     | 375
Car          | ground    | 4     | 4  | $4753    | 49812
Space Ship   | space     | 3     | 1  | $121435  | 2029064
Space Ship   | space     | 3     | 1  | $121435  | 3043596
*******************************************************/
#include <tr1/memory> //need this so it works on flip
#include <iostream>
#include <cmath>
#include <string>
#include <boost/random.hpp>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;

boost::mt19937 gen(time(NULL)); //seed PRNG

/*
*   Vehicle class.  This is pretty much just a class with
*   virtual functions for the other subclasses and a
*   overloaded ostream for printing
*/
class vehicle{

    public:
        vehicle(){};
        ~vehicle(){};

        // these virtual functions need to actually be defined here
        // for the ostream overload to work.
        virtual const string& transport(){
            return this->trans;
        };
        virtual const string& getName(){
            return this->name;
        };
        virtual const int& getWheels(){
            return this->wheels;
        };
        virtual const int& getDoors(){
            return this->doors;
        };
        virtual const int& getPrice(){
            return this->price;
        };
        virtual const int& getMiles(){
            return this->miles;
        };

        virtual void setName(const string& n){};

        virtual void setWheels(const int& w){};

        virtual void setChar(const char& c){};

        friend std::ostream& operator <<(std::ostream& outs, vehicle &v){
            outs << std::setw(13) << std::left << v.getName()  << "| "<< std::setw(10)
            << v.transport() << "| " << std::setw(6) << v.getWheels() << "| " << std::setw(3)
            << v.getDoors() << "| $" << std::setw(6) << v.getPrice() << "  | " << v.getMiles();
            return outs;
        }

    protected:
        string trans;
        int wheels;
        string name;
        int doors;
        int miles;
        int price;
        char test;

};

/*
*   Each subclass uses its own constructor to set each variable
*
*/
class car : public vehicle{

    public:

        car(int p = 0, int m = 0){
            this->trans = "ground";
            this->wheels = 4;
            this->name = "Car";
            this->doors = 4;
            this->price =  p*4753/m;
            this->miles =  m*12453;
        }


        void settransport(const string& t){
            this->trans = t;
        }

        void setName(const string& n){
            this->name = n;
        }

        void setWheels(const int& w){
            this->wheels = w;
        }

        void setDoors(const int& d){
            this->doors = d;
        }

        void setChar(const char &c){
            this->test = c;
        }

};

class bike : public vehicle{

    public:

        bike(int p = 0, int m = 0){
            this->trans = "ground";
            this->wheels = 2;
            this->name = "Bike";
            this->doors = 0;
            this->price =  p*984/m;
            this->miles =  m*125;
        }

        void settransport(const string& t){
            this->trans = t;
        }

        void setName(const string& n){
            this->name = n;
        }

        void setWheels(const int& w){
            this->wheels = w;
        }

        void setDoors(const int& d){
            this->doors = d;
        }

                void setChar(const char &c){
            this->test = c;
        }

};

class boat : public vehicle{

    public:

        boat(int p = 0, int m = 0){
            this->trans = "Water";
            this->wheels = 0;
            this->name = "Boat";
            this->doors = 0;
            this->price =  p*21542/m;
            this->miles =  m*1213;
        }

        void settransport(const string& t){
            this->trans = t;
        }

        void setName(const string& n){
            this->name = n;
        }

        void setWheels(const int& w){
            this->wheels = w;
        }

        void setDoors(const int& d){
            this->doors = d;
        }

                void setChar(const char &c){
            this->test = c;
        }

};

class plane : public vehicle{

    public:

        plane(int p = 0, int m = 0){
            this->trans = "Air";
            this->wheels = 3;
            this->name = "Plan";
            this->doors = 2;
            this->price =  p*145021/m;
            this->miles =  m*2145;
        }

        void settransport(const string& t){
            this->trans = t;
        }

        void setName(const string& n){
            this->name = n;
        }

        void setWheels(const int& w){
            this->wheels = w;
        }

        void setDoors(const int& d){
            this->doors = d;
        }

                void setChar(const char &c){
            this->test = c;
        }

};

class space_ship : public vehicle{
    using vehicle::getMiles;

    public:

        space_ship(int p = 0, int m = 0){
            this->trans = "space";
            this->wheels = 3;
            this->name = "Spac";
            this->doors = 1;
            this->price =  p*121435/m;
            this->miles =  m*1014532;
        }

        void settransport(const string& t){
            this->trans = t;
        }

        void setName(const string& n){
            this->name = n;
        }

        void setWheels(const int& w){
            this->wheels = w;
        }

        void setDoors(const int& d){
            this->doors = d;
        }

                void setChar(const char &c){
            this->test = c;
        }

};

typedef std::tr1::shared_ptr<vehicle> vehicle_ptr;

/*
* take a vector of vehicle pointers and fill with different types of
* vehicles.
*/
void fillVehicles(std::vector<vehicle_ptr> &vehicle, int numVehicles){
    cout << "Initializing " << numVehicles << " random vehicles" <<endl;

    // generate some random numbers to fill the vehicle array
    boost::uniform_int<> dist(1,5);
    boost::variate_generator<boost::mt19937&,
      boost::uniform_int<> > rng(gen, dist);

    // loop for the number of vehicles requested and create
    // a new object.  Push back to the vector.
    for(int i = 0; i < numVehicles; ++i){

        int type = rng(); // type of vehicle #1-5
        int tempMiles = rng(); // miles just for printint realistic data
        int tempPrice = rng(); // price just for printing realistic data

            switch(type){
                case 1:
                    vehicle.push_back(std::tr1::shared_ptr<car>(
                                    new car(tempPrice, tempMiles)));
                    break;

                case 2:
                    vehicle.push_back(std::tr1::shared_ptr<bike>(
                                    new bike(tempPrice, tempMiles)));
                    break;

                case 3:
                    vehicle.push_back(std::tr1::shared_ptr<plane>(
                                    new plane(tempPrice, tempMiles)));
                    break;

                case 4:
                    vehicle.push_back(std::tr1::shared_ptr<space_ship>(
                                    new space_ship(tempPrice, tempMiles)));
                    break;

                case 5:
                    vehicle.push_back(std::tr1::shared_ptr<boat>(
                                    new boat(tempPrice, tempMiles)));
                    break;
            }
        }
}



/*
*   Print out the vehicles.  Takes in the vector of
*   shared pointers and iterates over the length
*   of the vector.  This give a an iterator to
*   a shared pointer to an object so it needs
*   to be dereferanced twice. The object is printed
*   using the overloaded << operator from the vehicle
*   class.
*/
void print(std::vector<vehicle_ptr> &v){

    cout << "\033[1;4;37;40mVehicle Type  Transport  Wheels  Doors  Price     Miles\033[0m" << endl;
    for(auto i = v.begin(); i != v.end(); ++i){
        cout << "\033[4;37;40m" << **i << "\033[0m" << endl;
    }
}


int main(int argc, char **argv)
{

    int numVehicles;

    cout << "Enter the number of vehicles" << endl;
    cout << "Up to 10 max, or an error will be thrown" << endl;

    // this checks to see that the user entered value is 10 or less
    // throws an error if it is greater and sets it to 10
//    try{
//        cin >> numVehicles;
//        if (numVehicles > 10){
//            throw 1;
//        }
//    }
//    catch(int e){
//        cout << "Error: " << e << endl;
//        cout << "Number of vehicles is too high.. setting to max of 10" << endl;
        numVehicles = 10;
   // }

    // declare a vector of shared pointers
    std::vector<vehicle_ptr> vehicleLot;

    // fill the vector with vehicles
    fillVehicles(vehicleLot, numVehicles);

    print(vehicleLot);

    vehicleLot[0]->setWheels(2); // change an Integer

    vehicleLot[0]->setName("asdf"); // change a string

    vehicleLot[0]->setChar('a'); // change a char

	return 0;
}
