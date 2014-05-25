#include "limits.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using std::endl;
using std::cout;

using namespace std;

namespace AS6{

	class PrimeNumber{

	    public:

	    //constructor
	    PrimeNumber(int prime = 1){
	        this->prime = static_cast<int>(prime);
	    }

        // getters
        int getPrime();

        // setteres
        void setPrime(int prime);

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

        int operator--(){
            if(prime == 1){
                this->prime = 1;
                return 1;
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

        int isPrime(int input);

	    private:

            int prime;

	};

    class RationalNumber{

        public:

            RationalNumber(int num = 0, int denom = 1){
                this->numerator = static_cast<int>(num);
                this->denominator = static_cast<int>(denom);
            }

            RationalNumber(int wholeNumber){
                this->numerator = static_cast<int>(wholeNumber = 0);
                this->denominator = 1;
            }

            void setNumbers(int num, int denom){
                this->numerator = static_cast<int>(num);
                this->denominator = static_cast<int>(denom);
            }

            friend ostream& operator <<(ostream& outs, const RationalNumber& rational);

            friend istream& operator >>(istream& ins,  RationalNumber& rational){
                int num, denom;
                ins >> num;
                ins >> denom;
                rational.numerator = num;
                rational.denominator = denom;

                return ins;
            }

            friend const RationalNumber operator +(const RationalNumber& rational1, RationalNumber& rational2);
            friend const RationalNumber operator -(const RationalNumber& rational1, RationalNumber& rational2);
            friend const RationalNumber operator *(const RationalNumber& rational1, RationalNumber& rational2);
            friend const RationalNumber operator /(const RationalNumber& rational1, RationalNumber& rational2);
            friend bool operator ==(const RationalNumber& rational1, RationalNumber& rational2);
            friend bool operator <(RationalNumber& rational1, RationalNumber& rational2);
            friend bool operator <=(RationalNumber& rational1, RationalNumber& rational2);
            friend bool operator >(RationalNumber& rational1, RationalNumber& rational2);
            friend bool operator >=(RationalNumber& rational1, RationalNumber& rational2);

        private:
            int numerator, denominator;

            void normalize();
    };

    class ComplexNumber{

        public:

        ComplexNumber(){
            this->imag = 0;
            this->real = 0;
        }

        ComplexNumber( RationalNumber& r1,  RationalNumber& r2){
            Rat1 = r1;
            Rat2 = r2;
        }

        ComplexNumber(double re, double im = 0){
            this->imag = static_cast<double>(im);
            this->real = static_cast<double>(re);
        }

        void setValues(double re, double im){
            this->imag = static_cast<double>(im);
            this->real = static_cast<double>(re);
        }

        friend ostream& operator <<(ostream& outs, const ComplexNumber c1){
                if(c1.imag > 0){
                    outs << c1.real << "+" << c1.imag << "i";
                    return outs;
                }

                if(c1.imag == 0){
                    outs << c1.real;
                    return outs;
                }
                else{
                    outs << c1.real << c1.imag << "i";
                    return outs;
                }
            }

        friend const ComplexNumber operator +(const ComplexNumber& c1, const ComplexNumber& c2);
        friend const ComplexNumber operator -(const ComplexNumber& c1, const ComplexNumber& c2);
        friend const ComplexNumber operator *(const ComplexNumber& c1, const ComplexNumber& c2);
        friend const ComplexNumber operator /(const ComplexNumber& c1, const ComplexNumber& c2);

        const ComplexNumber conj(ComplexNumber c1){
            ComplexNumber temp(c1.real, -1*c1.imag);
            return temp;
        }

        double polar();

        private:

        double real, imag;
        RationalNumber Rat1, Rat2;

    };

}
