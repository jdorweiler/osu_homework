
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, const char * argv[]) {

int value, i;

    for(i = 97; i < 200; ++i){
        printf("%d  %f \n", i, (int)sin(i));
    }

return 0;
}

