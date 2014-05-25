/******************************************************
** Author: Jason Dorweiler
** Date: 11-10-13
** Description: CS165 Assignment 6
** Input: ./ComplexNumber then follow prompts
** Output:
Enter a complex number: real and imaginary
1.2
4
Enter another complex number: real and imaginary
2
3
Testing copy constructor
Complex number 3 (2,3) is a copy of complex number 2 (2,3)

Complex Number 1 is (1.2,4)
Complex Number 2 is (2,3)

Adding complex numbers
Using my class (1.2,4) + (2,3) = (3.2,7)
Using std::Complex (1.2,4) + (2,3) = (3.2,7)

Subtracting complex numbers
Using my class (1.2,4) - (2,3) = (-0.8,1)
Using std::Complex (1.2,4) - (2,3) = (-0.8,1)

Multiplying complex numbers
Using my class (1.2,4) * (2,3) = (-9.6,11.6)
Using std::Complex (1.2,4) * (2,3) = (-9.6,11.6)

The Complex conjugate of each number
Using my class (1.2,4) conjugate is (1.2,-4)
Using std::Complex (1.2,4) conjugate is (1.2,-4)

Dividing complex numbers
Using my class (1.2,4) / (2,3) = (1.10769,0.338462)
Using std::Complex (1.2,4) / (2,3) = (1.10769,0.338462)

Convert to Polar
Using my class (1.2,4) converte to polar is (4.17612,73.3008)
Using std::Complex (1.2,4) converted to polar is (5.01135,16.7045)

Normalize
Using my class (1.2,4) normalized is 17.44
Using std::Complex (1.2,4) normalized is 17.44

Absolute Value
Using my class (1.2,4) abs is 4.17612
Using std::Complex (1.2,4) abs is 4.17612

Unary -
Using my class (1.2,4) unary - is (-1.2,-4)
Using std::Complex (1.2,4) unary - is  (-1.2,-4)

*******************************************************/
#include "as6.h"
#include <complex>

using AS6::ComplexNumber;

int main(){

    // create two complex numbers
    ComplexNumber complexNum1, complexNum2;

    cout << "Enter a complex number: real and imaginary" << endl;
    cin >> complexNum1;

    cout << "Enter another complex number: real and imaginary" << endl;
    cin >> complexNum2;

    // test copy constructor
    cout << "Testing copy constructor " << endl;
    ComplexNumber complexNum3 = complexNum2;
    cout << "Complex number 3 " << complexNum3 << " is a copy of complex number 2 " << complexNum2 << endl << endl;

    // create two std::complex copies to compare the two classes
    std::complex<double> stdComplex1(complexNum1.Real(),complexNum1.Imag()), stdComplex2(complexNum2.Real(),complexNum2.Imag());

    cout << "Complex Number 1 is " << complexNum1 << endl;
    cout << "Complex Number 2 is " << complexNum2 << endl << endl;

    cout << "Adding complex numbers" << endl;
    cout << "Using my class " << complexNum1 << " + " << complexNum2 << " = " << complexNum1+complexNum2 << endl;
    cout << "Using std::Complex " << stdComplex1 << " + " << stdComplex2 << " = " << stdComplex1+stdComplex2 << endl << endl;

    cout << "Subtracting complex numbers" << endl;
    cout << "Using my class " << complexNum1 << " - " << complexNum2 << " = " << complexNum1-complexNum2 << endl;
    cout << "Using std::Complex " << stdComplex1 << " - " << stdComplex2 << " = " << stdComplex1-stdComplex2 << endl << endl;

    cout << "Multiplying complex numbers" << endl;
    cout << "Using my class " << complexNum1 << " * " << complexNum2 << " = " << complexNum1*complexNum2 << endl;
    cout << "Using std::Complex " << stdComplex1 << " * " << stdComplex2 << " = " << stdComplex1*stdComplex2 << endl << endl;

    cout << "The Complex conjugate of each number" << endl;
    cout << "Using my class " << complexNum1 << " conjugate is " << complexNum1.conj() << endl;
    cout << "Using std::Complex " << stdComplex1 << " conjugate is " << conj(stdComplex1) << endl << endl;

    cout << "Dividing complex numbers" << endl;
    cout << "Using my class " << complexNum1 << " / " << complexNum2 << " = " << complexNum1/complexNum2 << endl;
    cout << "Using std::Complex " << stdComplex1 << " / " << stdComplex2 << " = " << stdComplex1/stdComplex2 << endl << endl;

    cout << "Convert to Polar" << endl;
    cout << "Using my class " << complexNum1 << " converte to polar is " << complexNum1.polar() << endl;
    // No idea why this doesn't work for the std::complex but I know my conversion works.
    cout << "Using std::Complex " << stdComplex1 << " converted to polar is " << polar(norm(stdComplex1), arg(stdComplex1)) << endl << endl;

    cout << "Normalize" << endl;
    cout << "Using my class " << complexNum1 << " normalized is " << complexNum1.norm() << endl;
    cout << "Using std::Complex " << stdComplex1 << " normalized is " << norm(stdComplex1) << endl << endl;

    cout << "Absolute Value" << endl;
    cout << "Using my class " << complexNum1 << " abs is " << complexNum1.abs() << endl;
    cout << "Using std::Complex " << stdComplex1 << " abs is " << abs(stdComplex1) << endl << endl;

    cout << "Unary -" << endl;
    cout << "Using my class " << complexNum1 << " unary - is " << -complexNum1 << endl;
    cout << "Using std::Complex " << stdComplex1 << " unary - is  " << -stdComplex1 << endl << endl;

}
