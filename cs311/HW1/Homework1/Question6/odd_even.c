/*

Author: Jason Dorweiler
Email: dorweilj@onid.oregonstate.edu
Class: cs311-400
Assignment: Homework 1

 */


#include<stdio.h>
 
int main()
{
   int n;
 
   printf("Enter an integer\n");
   scanf("%d", &n);
 
   if( (n & 1) == 1 )
   {
      printf("Odd\n");
    }
   else{
      printf("Even\n");
   }
 
   return 0;
}
