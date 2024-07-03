#ifndef NUMBER_H
#define NUMBER_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h> 
#include "operation.h"

/** Exit status indicating that the program was given invalid input. */
#define FAIL_INPUT 102

/** Long Min for the base negatives 32*/
#define LONG_MIN_BASE32 -8000000000000

typedef struct {
    int base;
    char* expression;
} ExpressionData;

/** Function to skip spaces*/
char* skipSpace(char* expression);
/** Function to print a value*/
void printValue(long val);
/** Function to parse Values]*/
long parseValue(char* expression, int* i);
/** Function to convert digits to base 10*/
long convertDigitToBase10(char digit, int base);
/** Function to conver base to base 10*/
char* convertBaseNtoBase10(const char* expression, int base);
/** Function to conver to a chosen base*/
void convertToBase(long val, int base);
/** Function to check if it is a valid digit*/
int isValidDigit(int digit, int base);
/** Function to check the number of operators*/
int numberOfOperators(char* expression);
/** Function to parse the full expression*/
ExpressionData parseExpression(const char* expressionString);
#endif // NUMBER_H