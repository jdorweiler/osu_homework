/* CS261- Assignment 1 - Q.3*/
/* Name: Jason Dorweiler
 * Date: 1/6/14
 * Solution description: sorts an array
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
     int temp;
     int repeat = 1;
     while(repeat){
         repeat = 0;
         for(int i = 0; i  < n; i++){
                if(number[i] > number[i+1]){
                    temp = number[i];
                    number[i] = number[i+1];
                    number[i+1] = temp;
                    repeat = 1;
                }
         }
     }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 200;
    /*Allocate memory for an array of n integers using malloc.*/
    int *array = malloc(n*sizeof(int));
    /*Fill this array with random numbers, using rand().*/
    srand((int)time(NULL));
    for(int i = 0; i < n; i++){
        array[i] = rand()%100;
    }
    /*Print the contents of the array.*/
     printf("Unsorted Array:\n");
    for(int i = 0; i < n; i++){
        printf("%d\n", array[i]);
    }
    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    /*Print the contents of the array.*/
     printf("Sorted Array:\n");
    for(int i = 0; i < n; i++){
        printf("%d\n", array[i]);
    }
    return 0;
}
