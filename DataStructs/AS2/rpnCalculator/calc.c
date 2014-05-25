/******************************************************
** Author: Jason Dorweiler
** Date: 1/23/14
** Description: CS261 Assignment 2
** RPN calculator
** Input: ./calc 5 3 +
** Output: Result: 8.0000
******************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"
#include <assert.h>

#define Pi 3.14159265
#define e  2.7182818

/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 1);
	double temp1, temp2;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	temp2 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, temp2+temp1);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 1);
    double temp1, temp2;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	temp2 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, temp2-temp1);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 1);
    double temp1, temp2;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	temp2 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, temp2/temp1);
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	multiplied and pushed back onto the stack.
*/
void mult(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 1);
    double temp1, temp2;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	temp2 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, temp2*temp1);
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	return temp1^temp2.
*/
void power(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 1);
    double temp1, temp2;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	temp2 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, powf(temp2,temp1));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return its square.
*/
void square(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, powf(temp1,2));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return its cube.
*/
void cube(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, powf(temp1,3));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return its absolute value
*/
void absolute(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, abs(temp1));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return its square root
*/
void sqroot(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, sqrtf(temp1));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return e^number.
*/
void exponent(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, expf(temp1));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return natural log
*/
void nlog(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, logf(temp1));
}
/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and
	return base 10 log
*/
void tlog(struct DynArr *stack)
{
    assert(sizeDynArr(stack) > 0);
    double temp1;
	temp1 = topDynArr(stack);
	popDynArr(stack);
	pushDynArr(stack, log10f(temp1));
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++)
	{
		s = inputString[i];

		if(strcmp(s, "+") == 0)
			add(stack);
		else if(strcmp(s,"-") == 0)
			subtract(stack);
		else if(strcmp(s, "/") == 0)
			divide(stack);
		else if(strcmp(s, "x") == 0)
			mult(stack);
		else if(strcmp(s, "^") == 0)
			power(stack);
		else if(strcmp(s, "^2") == 0)
			square(stack);
		else if(strcmp(s, "^3") == 0)
			cube(stack);
		else if(strcmp(s, "abs") == 0)
			absolute(stack);
		else if(strcmp(s, "sqrt") == 0)
			sqroot(stack);
		else if(strcmp(s, "exp") == 0)
			exponent(stack);
		else if(strcmp(s, "ln") == 0)
			nlog(stack);
		else if(strcmp(s, "log") == 0)
			tlog(stack);
		else
		{
		    // push e to stack
			if(strcmp(s, "e") == 0)
                pushDynArr(stack, e);
            // push pi to stack
            else if(strcmp(s, "pi") == 0 || strcmp(s, "Pi") == 0)
                pushDynArr(stack, Pi);
            else {
                // check to see if s is a number
                if(isNumber(s, &result)){
                    pushDynArr(stack, result);
                }
                else{
                    printf("I don't understand this char %s\n", s);
                    goto exit; // we got bad input. get out of program
                }
            }
		}
	}	//end for

	 // store the result
	 result  = topDynArr(stack);

	 // pop last value off stack
	 popDynArr(stack);

	 // see if stack is empty
	 if(!isEmptyDynArr(stack)){
        printf("Invalid number of values or operands");
        goto exit; // exit program
	 }

	return result;

	exit:
	    return NAN; // main loop checks for NAN result
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

    double result = calculate(argc,argv);

    // check for NAN result to exit if there was bad input
    if(!isnan(result)){
        // print the final result
        printf("Result: %f\n", result);
    }
	return 0;
}
