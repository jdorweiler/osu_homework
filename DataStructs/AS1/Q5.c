/* CS261- Assignment 1 - Q.5*/
/* Name: Jason Dorweiler
 * Date: 1/8/14
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
     /*check to see if the char is already
       upper or lower case before sending
       it to the corresponding funciton
     */
     int i = 0;
     int chr;
     while(word[i]!= '\0'){
        chr = word[i];
        if(!(i%2) && chr > 96){ // char is lower and odd
            word[i] = toUpperCase(word[i]);
            ++i;
        }
        if((i%2) && chr < 97){ // char is upper and even
            word[i] = toLowerCase(word[i]);
            ++i;
        }
        ++i;
     }
}

void print(char* word){
    int i = 0;
    while(word[i] != '\0'){
        printf("%c",word[i]);
        ++i;
     }
     printf("\n");
}

int main(){
    /*Read word from the keyboard using scanf*/
    char str [20];
    printf("Enter a word: ");
    scanf("%s",str);
    /*Call sticky*/
    sticky(str);
    /*Print the new word*/
    print(str);

    return 0;
}
