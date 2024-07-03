#ifndef OPERATION_H
#define OPERATION_H
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h> 

/** Exit status for when an overflow occurs. */
#define FAIL_OVERFLOW 100

/** Exit status for when we try to divide by zero. */
#define FAIL_DIVZERO 101

/** Exit status for when negative exponent. */
#define FAIL_NEGEXP 103

/** Exit status for when fail input . */
#define FAIL_INPUT 102

#define MAX_SIZE 10000  

// Define a stack structure
typedef struct {
    union {
        long longArr[MAX_SIZE];
        char charArr[MAX_SIZE];
    };
    int top;
    int isCharStack;
} Stack;

/** Function to add*/
long plus(long a, long b);
/** Function to subtract*/
long minus(long a, long b);
/** Function to multiply*/
long times(long a, long b);
/** Function to exponentiate*/
long exponentiate(long a, long b);
/** Function to divide*/
long divide(long a, long b);
/** Function to apply operator*/
long applyOp(long a, long b, char op);
/** Function to check validity*/
int isValid(char* expression);
/** Function to check precedence*/
int precedence(char op);
/** Function to check if it is a operator*/
bool isOperator(char character);
/** Function to check top char*/
char topChar(Stack* stack);
/** Function to use top*/
long top(Stack* stack);
/** Function to pop char*/
char popChar(Stack* stack);
/** Function to pop*/
long pop(Stack* stack);
/** Function to push char*/
void pushChar(Stack* stack, char value);
/** Function to push*/
void push(Stack* stack, long value);
/** Function to check if full*/
int isFull(Stack* stack);
/** Function to check if empty*/
int isEmpty(Stack* stack);
/** Function to intitialize a stack*/
void initializeStack(Stack* stack, int isCharStack);


#endif /*OPERATION_H*/