/* CS261- Assignment 1 - Q.4*/
/* Name: Jason Dorweiler
 * Date: 1/8/14
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
     struct student *temp = malloc(sizeof(struct student));
     int repeat = 1;
     while(repeat){
         repeat = 0;
         for(int i = 0; i  < n - 1; i++){
                if(students[i].score > students[i+1].score){
                    *temp = students[i];
                    students[i] = students[i+1];
                    students[i+1] = *temp;
                    repeat = 1;
                }
         }
     }
}

void generate(struct student* students, int NUM_STUDENTS){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    srand((int)time(NULL));
    int temp_id;
    for(int i = 0; i < NUM_STUDENTS; i++){
        int getId = 1;
        while(getId){
            getId = 0;
            temp_id = rand()%10+1; // generate random student ID
            for(int j = 0; j < NUM_STUDENTS - 1; j++){
                if( students[j].id == temp_id){
                    getId = 1;
                    break;
                }
            }
        }
        students[i].id = temp_id;
        students[i].score = rand()%100;
    }
}

void output(struct student* students, int NUM_STUDENTS){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    for(int i = 0; i < NUM_STUDENTS ; i++){
        printf("ID: %d Score: %d\n", students[i].id, students[i].score);
    }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 10;

    /*Allocate memory for n students using malloc.*/
    struct student *students = malloc(n * sizeof(struct student));

    /*Generate random IDs and scores for the n students, using rand().*/
    generate(students, n);

    /*Print the contents of the array of n students.*/
    output(students, n);
    /*Pass this array along with n to the sort() function*/
    sort(students, n);
    printf("\n");
    /*Print the contents of the array of n students.*/
    output(students, n);

    return 0;
}
