/******************************************************
** Author: Jason Dorweiler
** Date: 10-1-13
** Description: CS165 programming lab 4 bouyancy
** Input: weight, radius
** Output:
Please enter the weight (lbs): 1
Please enter the radius: 10
The sphere will float!

******************************************************/


#include <iostream>
#include <cmath>
//Defines the specific weight of water
#define WATER_WEIGHT 62.4;
#define PI 3.14

using std::cout;
using std::cin;

int main() {

    //Variables needed to calculate buoyancy
    float radius, bforce, volume, weight;

    //Prompt user for weight and radius of sphere
    cout << "Please enter the weight (lbs): ";
    cin >> weight;
    cout << "Please enter the radius: ";
    cin >> radius;

    //Calculate the volume and buoyancy force
    volume = 4./3. * PI * pow(radius, 3);
    bforce = volume * WATER_WEIGHT;

    //Determine if the sphere will sink or float
    if(bforce >= weight) {
        cout << "The sphere will float!\n";
    }
    else  {cout << "The sphere will sink!\n";}

return 0;
}
