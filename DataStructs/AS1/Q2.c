/* CS261- Assignment 1 - Q.2*/
/* Name: Jason Dorweiler
 * Date: 1/6/14
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a*2;
    /*Set b to half its original value*/
    *b = *b/2;
    /*Assign a+b to c*/
    c = *a+*b;
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int c;
    /*Print the values of x, y and z*/
    printf("x: %d y: %d z: %d\n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    c = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("value returned from foo: %d\n", c);
    /*Print the values of x, y and z again*/
    printf("x: %d y: %d z: %d\n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/

    /*
        z was passed by value to foo().  This means that
        the value of z was never changed inside of the funciton and
        instead a new copy of the value was made.
    */
    return 0;
}


