/* CS261- Assignment 1 - Q. 0*/
/* Name: Jason Dorweiler
 * Date: 1/6/14
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
    printf("Value pointed to by iptr: %d\n", *iptr);
     /*Print the address pointed to by iptr*/
    printf("Address pointed to by iptr: %p\n", iptr);
     /*Print the address of iptr itself*/
     printf("Address of iptr: %p\n", &iptr);
}

int main(){

    /*declare an integer x*/
    int x = 10;
    /*print the address of x*/
    printf("Address of X: %p\n",&x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("The value of X: %d\n", x);

    return 0;
}
