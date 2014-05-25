#include "as6.h"


namespace AS6{
    // Member functions
    int PrimeNumber::getPrime(){
                return prime;
            }

    void PrimeNumber::setPrime(int prime){
                    this->prime = static_cast<int>(prime);
            }

    int PrimeNumber::isPrime(int input){
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

    void RationalNumber::normalize(){

                if(denominator < 0){
                    denominator = -denominator;
                    numerator = -numerator;
                }
                int x, y;

                x = abs(numerator);
                y = abs(denominator);

                while(y){
                    int t = y;
                    y = x%y;
                    x = t;
                }

                if(x > 1){
                    numerator /= x;
                    denominator /= x;
                }
            }

    double ComplexNumber::polar(){
        double temp = sqrt(pow(real,2)+pow(imag,2));
        double temp2 = exp(sqrt(-1)*atan(imag/real));
        return temp;
    }

    // friend functions

    ostream& operator <<(ostream& outs, const RationalNumber& rational){
                outs << rational.numerator << "/" << rational.denominator;
                return outs;
            }

    bool operator >=(RationalNumber& rational1, RationalNumber& rational2){

                rational1.normalize();
                rational2.normalize();

                bool equal = rational1 == rational2;

                if(equal || (rational1 > rational2)){
                    return true;
                }
                return false;
            }

    bool operator >(RationalNumber& rational1, RationalNumber& rational2){

                if(!(rational1 <= rational2)){
                    return true;
                }
                return false;
            }

    bool operator <=(RationalNumber& rational1, RationalNumber& rational2){

                rational1.normalize();
                rational2.normalize();

                bool equal = rational1 == rational2;

                if((equal || (rational1 < rational2))){
                    return true;
                }
                return false;
            }

    bool operator <(RationalNumber& rational1, RationalNumber& rational2){

                rational1.normalize();
                rational2.normalize();

                if((rational1.numerator * rational2.denominator) < (rational2.numerator * rational1.denominator)){
                    return true;
                }
                return false;
            }

    bool operator ==(const RationalNumber& rational1, RationalNumber& rational2){

                if(rational1.numerator*rational2.denominator == rational2.numerator*rational1.denominator){
                    return true;
                }
                else{
                    return false;
                }
            }

    const RationalNumber operator /(const RationalNumber& rational1, RationalNumber& rational2){
                RationalNumber temp(rational1.numerator*rational2.denominator, rational1.denominator*rational2.numerator);
                temp.normalize();
                return temp;

            }

    const RationalNumber operator *(const RationalNumber& rational1, RationalNumber& rational2){
                RationalNumber temp(rational1.numerator*rational2.numerator, rational1.denominator*rational2.denominator);
                temp.normalize();
                return temp;
            }

    const RationalNumber operator +(const RationalNumber& rational1, RationalNumber& rational2){
                int tempNum1, tempNum2, tempDenom;

                tempNum1 = rational1.numerator*rational2.denominator;
                tempNum2 = rational2.numerator*rational1.denominator;
                tempDenom = rational1.denominator * rational2.denominator;
                tempNum1 = tempNum1+tempNum2;
                RationalNumber temp(tempNum1, tempDenom);

                temp.normalize();

                return temp;
    }

    const RationalNumber operator -(const RationalNumber& rational1, RationalNumber& rational2){
                int tempNum1, tempNum2, tempDenom;

                tempNum1 = rational1.numerator*rational2.denominator;
                tempNum2 = rational2.numerator*rational1.denominator;
                tempDenom = rational1.denominator * rational2.denominator;

                RationalNumber temp(tempNum1-tempNum2, tempDenom);

                temp.normalize();

                return temp;

            }

    const ComplexNumber operator +(const ComplexNumber& c1, const ComplexNumber& c2){

            return ComplexNumber(c1.real+c2.real, c1.imag+c2.imag);
    }

    const ComplexNumber operator -(const ComplexNumber& c1, const ComplexNumber& c2){

            return ComplexNumber(c1.real-c2.real, c1.imag-c2.imag);
    }

    const ComplexNumber operator *(const ComplexNumber& c1, const ComplexNumber& c2){

            return ComplexNumber(c1.real*c2.real+(-1*c1.imag*c2.imag), c1.real*c2.imag+c1.imag*c2.real);
        }

    const ComplexNumber operator /(const ComplexNumber& c1, const ComplexNumber& c2){
        ComplexNumber temp(c2.real,-1*c2.imag);
        double tempN1, tempN2;

        tempN1 = (c1*temp).real/(c2*temp).real;
        tempN2 =  (c1*temp).imag/(c2*temp).real;
     //   RationalNumber rational1, rational2;
        // conj copy of c2
        cout << tempN1 << " " << tempN2 << endl;
    //    rational1.setNumbers(static_cast<int>((c1*temp).real), static_cast<int>((c2*temp).real));
    //    rational2.setNumbers(static_cast<int>((c1*temp).imag),static_cast<int>((c2*temp).real));

        ComplexNumber temp2(tempN1, tempN2);

        return temp2;
        }
}

