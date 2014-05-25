#include <stdio.h>
#include<stdlib.h>

int main(){
    int number;
    printf("enter a number: \n");
    scanf("%d", &number);

    if(number%2){
        printf("Your number %d is odd\n", number);
    }
    else{
        printf("Your number %d is even\n", number);
    }

    return 0;
}
