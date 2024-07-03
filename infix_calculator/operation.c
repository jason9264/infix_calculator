/** 
 * @file operation.c
 * @author Jason Wang
 * This program helps process the input using functions and operations.
*/
#include "operation.h"
#include <stdlib.h>
#include <limits.h>

/** Exit status for when an overflow occurs. */
#define FAIL_OVERFLOW 100

/** Exit status for when we try to divide by zero. */
#define FAIL_DIVZERO 101

/** Exit status for when negative exponent. */
#define FAIL_NEGEXP 103

/** Exit status for when fail input. */
#define FAIL_INPUT 102

#include "operation.h"

/** Adds two long values.
 * @param a the first value
 * @param b the second value
 * @return the sum of a and b
 */
long plus(long a, long b)
{
    if ((b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b)) {
        
        exit(FAIL_OVERFLOW);
    }
    return a + b;
}

/** Subtracts two long values.
 * @param a the first value
 * @param b the second value
 * @return the result of a and b
 */
long minus(long a, long b)
{
    if ((b > 0 && a < LONG_MIN + b) || (b < 0 && a > LONG_MAX + b)) {
        
        exit(FAIL_OVERFLOW);
    }
    return a - b;
}

/** Multiplies two long values.
 * @param a the first value
 * @param b the second value
 * @return the total of a and b
 */
long times(long a, long b)
{
    if (a > 0) {
        if (b > 0 && a > LONG_MAX / b) {
            
            exit(FAIL_OVERFLOW);
        }
        if (b < 0 && b < LONG_MIN / a) {
            
            exit(FAIL_OVERFLOW);
        }
    } else if (a < 0) {
        if (b > 0 && a < LONG_MIN / b) {
            
            exit(FAIL_OVERFLOW);
        }
        if (b < 0 && (a != -1 || b != LONG_MIN)) {
            if (b < LONG_MAX / a) {
                
                exit(FAIL_OVERFLOW);
            }
        }
    }
    return a * b;
}

/** Exponentiates two long values.
 * @param a the first value
 * @param b the second value
 * @return the total of a and b
 */
long exponentiate(long a, long b)
{
    if (b < 0)
    {
        
        exit(FAIL_NEGEXP);
    }
    long result = 1;
    for (long i = 0; i < b; i++)
    {
        if (result > LONG_MAX / a) {
            
            exit(FAIL_OVERFLOW);
        }
        result *= a;
    }
    return result;
}

/** Divides two long values.
 * @param a the first value
 * @param b the second value
 * @return the division of a and b
 */
long divide(long a, long b)
{
    if (b == 0)
    {
        
        return FAIL_DIVZERO;
    }
    if (a == LONG_MIN && b == -1) {
        
        return FAIL_OVERFLOW;
    }
    return a / b;
}


/**
 * Initialize the stack
 * @param stack the stack
 * @param isCharStack indicates whether store character or integer
 */
void initializeStack(Stack* stack, int isCharStack) {
    stack->top = -1;
    stack->isCharStack = isCharStack;
}

/**
 * Check stack is empty
 * @param stack the stack
 * @return true if the stack is empty, false otherwise
 */
int isEmpty(Stack* stack) {
    return (stack->top == -1);
}

/**
 * Checks stack is full
 * @param stack the stack
 * @return true if full, false otherwise
 */
int isFull(Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}

/**
 * Push an element onto the stack.
 * @param stack stack to push the element to
 * @param value value to push to stack
 */
void push(Stack* stack, long value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push element.\n");
        return;
    }
    stack->top++;
    stack->longArr[stack->top] = value;
}

/**
 * Push a character to stack
 * @param stack stack to push character to
 * @param value character to push to stack
 */
void pushChar(Stack* stack, char value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push element.\n");
        return;
    }
    stack->top++;
    stack->charArr[stack->top] = value;
}

/**
 * Removes and return top element from stack
 * @param stack the stack
 * @return popped element
 */
long pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop element.\n");
        return -1;
    }
    long poppedElement = stack->longArr[stack->top];
    stack->top--;
    return poppedElement;
}

/**
 * Remove and return the top character from stack
 * @param stack the stack to pop
 * @return popped character
 */
char popChar(Stack* stack) {
    if (isEmpty(stack)) {
        exit(FAIL_INPUT);
        return '\0';
    }
    char poppedElement = stack->charArr[stack->top];
    stack->top--;
    return poppedElement;
}

/**
 * Retrieve top element of the stack without removal
 * @param stack stack to get element from
 * @return top element of the stack
 */
long top(Stack* stack) {
    if (isEmpty(stack)) {
        exit(FAIL_INPUT);
        return -1;
    }
    return stack->longArr[stack->top];
}

/**
 * Retrieve top character of the stack without removal.
 * @param stack  stack to get top character
 * @return top character of stack
 */
char topChar(Stack* stack) {
    if (isEmpty(stack)) {
        exit(FAIL_INPUT);
        return '\0';
    }
    return stack->charArr[stack->top];
}

/**
 * Check if a character is an operator
 * @param character character to check
 * @return true if the character is operator
 */
bool isOperator(char character) {
    return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^');
}

/**
 * Determine the precedence of an operator
 * @param op operator
 * @return the precedence of the operator (1 for + and -, 2 for * and /, 3 for ^, 0 for others)
 */
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

/**
 * Apply given operator to the operands
 * @param a first operand
 * @param b second operand
 * @param op operator to apply
 * @return result of applying the operator to the operands
 */
long applyOp(long a, long b, char op) {
    switch (op) {
        case '+':
            return plus(a,b);
        case '-':
            return minus(a,b);
        case '*':
            return times(a,b);
        case '/':
            if(b==0) return FAIL_DIVZERO;
            return divide(a,b);
        case '^':
            return exponentiate(a,b);
    }
    return 0;
}

/**
 * Checks if expression is valid
 * @param expression  expression to validate
 * @return 0 if the expression is valid, otherwise an error code
 */
int isValid(char* expression) {

    int expression_length = strlen(expression);

    for (int i = 0; i < expression_length; i++) 
    {
        // Check for divide by zero
        if (expression[i] == '/' && expression[i + 1] == '0') {
            
            exit(FAIL_DIVZERO);
        }
        // Check for double operators
        if (expression[i] == '+'  || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            if (i < expression_length - 1 && (expression[i] == expression[i + 1])) {
               
                exit(FAIL_INPUT);
            }
        }

        // Check for invalid characters (excluding numbers and operators)
        if (!isdigit(expression[i]) && expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '^') {
            
            exit(FAIL_INPUT);
        }

        // Check for negative exponents
        if (expression[i] == '^' && expression[i + 1] == '-') {
            return (FAIL_NEGEXP);
        }

    }
    return 0;  // Valid expression
}