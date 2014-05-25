/* CS261- Assignment 1 - Q.1*/
/* Name: Jason Dorweiler
 * Date: 1/6/14
 * Solution description:
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <assert.h>
#include <time.h>

#define NUM_STUDENTS 10

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *student = malloc(NUM_STUDENTS*sizeof(struct student));
     /*return the pointer*/
     return student;
}

void generate(struct student* students){
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

void output(struct student* students){
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

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int total = 0;
    int max = 0;
    int min = 100;
    for(int i = 0; i < NUM_STUDENTS ; i++){

        int temp_score = 0;
        temp_score = students[i].score;
        total += temp_score;

        if(temp_score > max){
            max = temp_score;
        }
        if(temp_score < min){
            min = temp_score;
        }
    }
    printf("Average: %d Min: %d Max: %d\n", total/NUM_STUDENTS, min, max);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    assert(stud != NULL);
    free(stud);
    printf("Deallocating...");

}

int main(){
    struct student* stud = NULL;

    /*call allocate*/
    stud = allocate();
    assert(stud != NULL);
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);
    return 0;
}
