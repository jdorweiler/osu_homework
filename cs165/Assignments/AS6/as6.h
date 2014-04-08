/******************************************************
** Author: Jason Dorweiler
** Date: 11-10-13
** Description: CS165 Assignment 6
Header file for the prime, rational, and complex number
classes
******************************************************/
#ifndef AS6_H
#define AS6_H

#include "limits.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

#define PI 3.14159265359

using std::endl;
using std::cout;

using namespace std;

// keep the three number classes in the AS6 namespace
namespace AS6{

	class PrimeNumber{

	    public:
            // destructor
            ~PrimeNumber(){};
            //constructor with default set to 2
            PrimeNumber(int prime = 2){
                this->prime = static_cast<int>(prime);
            }

            // get prime number
            int getPrime();

            // set prime number
            void setPrime(int prime);

            // overload ++ operator and and return next prime up to INT_MAX
            int operator++(){
                for(int i = prime+1; i < INT_MAX; i++)
                   for(int j = 2; j < INT_MAX; j++){
                        if(i % j == 0){
                            break;
                        }
                        else if(j+1 > sqrt(i)){
                            this->prime = i;
                            return i;
                        }
                   }
            }

            // overload -- operator and return next lowest down to min of 2
            int operator--(){
                if(prime == 2){
                    return 2;
                }

                for(int i = prime-1; i > 0; i--)

                    for(int j = 2; j < INT_MAX; j++){
                        if(i % j == 0){
                            break;
                        }
                        else if(j+1 > sqrt(i)){
                            this->prime = i;
                            return i;
                        }
                   }
            }

            // check to see if an integer is a prime number
            int isPrime(int input);

	    private:

            int prime;

	};

    class RationalNumber{

        public:

            // constructor with 0,1 as defaults.  Otherwise set to num,denom and normalize the input
            RationalNumber(int num = 0, int denom = 1){
                this->numerator = static_cast<int>(num);
                this->denominator = static_cast<int>(denom);
                normalize();
            }

            // constructor for whole number, sets the denominator to 1
            RationalNumber(int wholeNumber){
                this->numerator = static_cast<int>(wholeNumber = 0);
                this->denominator = 1;
                normalize();
            }

            // setter sets num, denom and normalizes
            void setNumbers(int num, int denom){
                this->numerator = static_cast<int>(num);
                this->denominator = static_cast<int>(denom);
                normalize();
            }

            friend ostream& operator <<(ostream& outs, const RationalNumber& rational);                             // overloaded output stream
            friend istream& operator >>(istream& ins,  RationalNumber& rational);                                   // overloaded input stream
            friend const RationalNumber operator +(const RationalNumber& rational1, RationalNumber& rational2);     // overloaded binary addition
            friend const RationalNumber operator -(const RationalNumber& rational1, RationalNumber& rational2);     // overloaded binary subtraction
            friend const RationalNumber operator *(const RationalNumber& rational1, RationalNumber& rational2);     // overloaded multiplication
            friend const RationalNumber operator /(const RationalNumber& rational1, RationalNumber& rational2);     // overloaded division
            friend bool operator ==(const RationalNumber& rational1, RationalNumber& rational2);                    // overloaded equality
            friend bool operator <(RationalNumber& rational1, RationalNumber& rational2);                           // overloaded less than
            friend bool operator <=(RationalNumber& rational1, RationalNumber& rational2);                          // overloaded lessthan equal
            friend bool operator >(RationalNumber& rational1, RationalNumber& rational2);                           // overloaded greater than
            friend bool operator >=(RationalNumber& rational1, RationalNumber& rational2);                          // overloaded greater than equal

        private:
            int numerator, denominator;

            void normalize();   // function to reduce fraction
    };

    class ComplexNumber{

        public:

            // constructor sets real and imag to zero
            ComplexNumber(){
                this->imag = 0;
                this->real = 0;
            }

            // my failed attempt at a constructor using rational numbers
            ComplexNumber( RationalNumber& r1,  RationalNumber& r2){
                Rat1 = r1;
                Rat2 = r2;
            }

            // constructor with default imaginary
            ComplexNumber(double re, double im = 0){
                this->imag = static_cast<double>(im);
                this->real = static_cast<double>(re);
            }

            ~ComplexNumber(){} // destructor

            //copy constructor
            ComplexNumber(const ComplexNumber& c1){
                this->real = c1.real;
                this->imag = c1.imag;
            }

            // set real and imaginary values
            void setValues(double re, double im){
                this->imag = static_cast<double>(im);
                this->real = static_cast<double>(re);
            }


            friend ostream& operator <<(ostream& outs, const ComplexNumber& c1);                        // overloaded output stream
            friend istream& operator >>(istream& ins, ComplexNumber& c1);                               // overloaded input stream
            friend const ComplexNumber operator +(const ComplexNumber& c1, const ComplexNumber& c2);    // overloaded addition
            friend const ComplexNumber operator -(const ComplexNumber& c1, const ComplexNumber& c2);    // overloaded subtraction, binary
            friend const ComplexNumber operator -(const ComplexNumber& c1);                             // overloaded subtraction, unary
            friend const ComplexNumber operator *(const ComplexNumber& c1, const ComplexNumber& c2);    // overloaded multiplication
            friend const ComplexNumber operator /(const ComplexNumber& c1, const ComplexNumber& c2);    // overloaded division

            ComplexNumber conj();   // returns the complex conjugate
            ComplexNumber polar();  // convert to polar
            double Real();          // get the real value
            double Imag();          // get the imaginary value
            double norm();          // return normalized value
            double abs();           // return the absolute value

        private:

            double real, imag;
            RationalNumber Rat1, Rat2;      // variables for my failed attempt at complex with rational numbers

    };

#endif /* AS6_H */

    // Member functions

    // returns the prime number
    int PrimeNumber::getPrime(){
                return prime;
            }

    // function to set the prime number
    void PrimeNumber::setPrime(int prime){
                    // first check to see if it is a prime. Set the number if it is.
                    if(isPrime(prime)){
                        this->prime = static_cast<int>(prime);
                    }

                    // if it is less than two just set to a default prime 2
                    // otherwise find the next largest prime and set to that
                    else{
                        if(prime < 2){
                            this->prime = 2;
                            return;
                        }

                        while(!isPrime(prime)){
                            prime++;
                        }
                        this->prime = static_cast<int>(prime);
                    }
            }

    // check to see if a number is a prime
    int PrimeNumber::isPrime(int input){
        if(input < 2){
            return 0;
        }
        // if it is 2 then it is prime
        if(input == 2){
            return 1;
        }
        // if not check the input%j up to INT_MAX
        // if it doesn't equal zero then it is prime.
        for(int i = input; i < INT_MAX; i++)
            for(int j = 2; j < INT_MAX; j++){
                if(i % j == 0){
                    return 0;
                }
                else if(j+1 > sqrt(i) && i > 0){
                    return 1;
                }
            }
        }

    // Normalize the rational numbers to reduced form
    void RationalNumber::normalize(){
                // if the denom is negitive then flip the values to make the numerator negative
                if(denominator < 0){
                    denominator = -denominator;
                    numerator = -numerator;
                }

                // new temp integers for the numerator and denominator
                int x, y;

                x = abs(numerator);
                y = abs(denominator);

                // This loop goes through the y=x%y calculation untill y = 0.
                // it then stores the x value to reduce the fraction to the lowest
                // form.
                while(y){
                    int t = y;
                    y = x%y;
                    x = t;
                }

                // use the x calculated above to reduce the fraction.
                if(x > 1){
                    numerator /= x;
                    denominator /= x;
                }
            }

    // convert a complex number to polar form.
    ComplexNumber ComplexNumber::polar(){
        ComplexNumber temp;

        // calculate the magnitude
        double mag = sqrt(pow(real,2)+pow(imag,2));

        // calculate the theta angle
        double theta = atan2(imag,real)*180/PI;

        // store in the temp complex number and return it.
        temp.setValues(mag, theta);
        return temp;
    }

    // get the real portion of a complex number
    double ComplexNumber::Real(){
        return real;
    }

    // get the imaginary portion of a complex number
    double ComplexNumber::Imag(){
        return imag;
    }

    // normalize a complex (return its magnitude squared)
    double ComplexNumber::norm(){
        return pow(sqrt(pow(real,2)+pow(imag,2)),2);
    }

    // absolute value of a complex number
    double ComplexNumber::abs(){
        // return the magnitude
        return sqrt(pow(real,2)+pow(imag,2));
    }

    // complex conjugate
    ComplexNumber ComplexNumber::conj(){
                ComplexNumber temp(real, -1*imag);
                return temp;
            }

    // Overloade input stream for the rational number class
    istream& operator >>(istream& ins,  RationalNumber& rational){
                // temp numerator and denominator
                int num, denom;
                ins >> num;
                ins >> denom;

                // check to see if integers were entered and output a warning if not
                while(!cin){
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "please enter integers" << endl;
                }

                // denom can't be zero
                if(denom == 0){
                    cout << "Denominator can't be zero, setting to 1" << endl;
                    rational.denominator = 1;
                    rational.numerator = num;
                }
                else{
                rational.numerator = num;
                rational.denominator = denom;
                }

                // normalize to reduce the fration
                rational.normalize();

                return ins;
            }

    // Overloaded input stream for the complex number class
    istream& operator >>(istream& ins,  ComplexNumber& rational){
                // store temp real and imag variables
                double re, im;
                ins >> re;
                ins >> im;

                //set the the real and imag of the rational number
                rational.real = re;
                rational.imag = im;

                return ins;
            }

    // overloaded output for complex numbers
    ostream& operator <<(ostream& outs, const ComplexNumber& c1){
                    outs << "(" << c1.real << "," << c1.imag << ")";
                    return outs;
            }

    // overloaded output stream for rational numbers
    ostream& operator <<(ostream& outs, const RationalNumber& rational){
                outs << rational.numerator << "/" << rational.denominator;
                return outs;
            }

    // greater than or equal overloaded operator
    bool operator >=(RationalNumber& rational1, RationalNumber& rational2){
                // normalize the two rationals
                rational1.normalize();
                rational2.normalize();

                // check equality
                bool equal = rational1 == rational2;

                if(equal || (rational1 > rational2)){
                    return true;
                }
                return false;
            }

    // greather than overloaded operator
    bool operator >(RationalNumber& rational1, RationalNumber& rational2){

                if(!(rational1 <= rational2)){
                    return true;
                }
                return false;
            }

    // lessthan or equal overlaoded operator
    bool operator <=(RationalNumber& rational1, RationalNumber& rational2){
                // normalize the inputs
                rational1.normalize();
                rational2.normalize();

                // check equality
                bool equal = rational1 == rational2;

                if((equal || (rational1 < rational2))){
                    return true;
                }
                return false;
            }

    // less than overloaded operator
    bool operator <(RationalNumber& rational1, RationalNumber& rational2){
                // normalize the inputs
                rational1.normalize();
                rational2.normalize();

                if((rational1.numerator * rational2.denominator) < (rational2.numerator * rational1.denominator)){
                    return true;
                }
                return false;
            }

    // overloaded == operator
    bool operator ==(const RationalNumber& rational1, RationalNumber& rational2){

                if(rational1.numerator*rational2.denominator == rational2.numerator*rational1.denominator){
                    return true;
                }
                else{
                    return false;
                }
            }

    // overloaded divison operator
    const RationalNumber operator /(const RationalNumber& rational1, RationalNumber& rational2){
                RationalNumber temp(rational1.numerator*rational2.denominator, rational1.denominator*rational2.numerator);
                temp.normalize();
                return temp;
            }

    // overloaded multiplicaton operator
    const RationalNumber operator *(const RationalNumber& rational1, RationalNumber& rational2){
                RationalNumber temp(rational1.numerator*rational2.numerator, rational1.denominator*rational2.denominator);
                temp.normalize();
                return temp;
            }

    // overloaded addition operator
    const RationalNumber operator +(const RationalNumber& rational1, RationalNumber& rational2){
                // store temp integers
                int tempNum1, tempNum2, tempDenom;

                tempNum1 = rational1.numerator*rational2.denominator;
                tempNum2 = rational2.numerator*rational1.denominator;

                // calculate the new denominator
                tempDenom = rational1.denominator * rational2.denominator;

                // calculate the new numerator
                tempNum1 = tempNum1+tempNum2;

                // store in temp rational number
                RationalNumber temp(tempNum1, tempDenom);

                temp.normalize();

                return temp;
    }

    // overloaded subtraction operator
    const RationalNumber operator -(const RationalNumber& rational1, RationalNumber& rational2){
                // store temp integers
                int tempNum1, tempNum2, tempDenom;

                tempNum1 = rational1.numerator*rational2.denominator;
                tempNum2 = rational2.numerator*rational1.denominator;

                // calculate the new denominator
                tempDenom = rational1.denominator * rational2.denominator;

                // store in temp rational number and return it
                RationalNumber temp(tempNum1-tempNum2, tempDenom);

                temp.normalize();

                return temp;

            }

    // overloaded addition for complex numbers
    const ComplexNumber operator +(const ComplexNumber& c1, const ComplexNumber& c2){

            return ComplexNumber(c1.real+c2.real, c1.imag+c2.imag);
    }

    // overloaded subtraction for complex numbers
    const ComplexNumber operator -(const ComplexNumber& c1, const ComplexNumber& c2){

            return ComplexNumber(c1.real-c2.real, c1.imag-c2.imag);
    }

    // overloaded unary subtraction for complex numbers
    const ComplexNumber operator -(const ComplexNumber& c1){

            return ComplexNumber(-c1.real, -c1.imag);
    }

    // overloaded multiplicaton for complex numbers
    const ComplexNumber operator *(const ComplexNumber& c1, const ComplexNumber& c2){

            return ComplexNumber(c1.real*c2.real+(-1*c1.imag*c2.imag), c1.real*c2.imag+c1.imag*c2.real);
        }

    // overloaded division operator for complex numbers
    const ComplexNumber operator /(const ComplexNumber& c1, const ComplexNumber& c2){

        // temp complex so we can use the complex multiplication overloaded operator
        ComplexNumber temp(c2.real,-1*c2.imag);
        double tempN1, tempN2;

        tempN1 = (c1*temp).real/(c2*temp).real;
        tempN2 =  (c1*temp).imag/(c2*temp).real;

        // my failed attemp to get it to print out as rational numbers
     //  RationalNumber rational1, rational2;
        // conj copy of c2
    //    rational1.setNumbers(static_cast<int>((c1*temp).real), static_cast<int>((c2*temp).real));
    //    rational2.setNumbers(static_cast<int>((c1*temp).imag),static_cast<int>((c2*temp).real));

        ComplexNumber temp2(tempN1, tempN2);

        return temp2;
        }
}
