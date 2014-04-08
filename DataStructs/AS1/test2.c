#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
    int n ;
printf("enter n\n");
scanf("%d",&n);
printf("you entered %d\n", n);

for (int i=2; i< n; i++){ // This is O(n)
        for (int j=2; j*j<=i; j++) // This is O(sqrt(n)
        {
            // These are constant time so they don't matter
            if (i % j == 0)
                break;
            else if (j+1 > sqrt(i)) {
                printf("%d\n", i);

            }
        }
}
}
