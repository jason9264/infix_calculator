/** 
 * @file infix.c
 * @author Jason Wang
 * This program calls on and calculates input equations. It can evaluate base 10 using infix_10 base 32 using infix_32 and a custom base n, infix_n.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "number.h"
#include "operation.h"


static long parse_mul_div();
static long parse_exp();

/**
 * Function for parsing and calculating exponents in the equation, called by parse_mul_div
 * @param expression the expression that this function is operating on
 * @return long value.
 */
static long parse_exp(char* expression) 
{
    Stack operands;
    Stack operators;
    initializeStack(&operands, 0); // 0 represents integer stack
    initializeStack(&operators, 1); // 1 represents character stack

    int expression_length = strlen(expression);
    bool flag = false;
    for (int i = 0; i < expression_length; i++) {
        if (expression[i] == ' ' || expression[i] == '\t' || expression[i] == '\v' || expression[i] == '\f' || expression[i] == '\r') {
            continue;
        }
        if (isdigit(expression[i]) || (expression[i] == '-' && (i == 0 || isOperator(expression[i - 1]) || expression[i - 1] == '('))) {
            long val = 0; 

            if (expression[i] == '-') {
                i += 1;
                flag = true;
            }

            val = parseValue(expression, &i);
            

            if (flag) {
                push(&operands, -1 * val);
                i--;
                flag = false;
                continue;
            }
            push(&operands, val);

            i--;
        } else if (isOperator(expression[i])) {
            while (!isEmpty(&operators) && precedence(topChar(&operators)) >= precedence(expression[i])) {

                long val2 = top(&operands);
                pop(&operands);

                long val1 = top(&operands);
                pop(&operands);

                char op = topChar(&operators);
                popChar(&operators);

                push(&operands, applyOp(val1, val2, op));
            }
            pushChar(&operators, expression[i]);
        } else if (expression[i] == '(') {
            pushChar(&operators, expression[i]);
        } else if (expression[i] == ')') {
            while (!isEmpty(&operators) && topChar(&operators) != '(') {
                long val2 = top(&operands);
                pop(&operands);

                long val1 = top(&operands);
                pop(&operands);

                char op = topChar(&operators);
                popChar(&operators);

                push(&operands, applyOp(val1, val2, op));
            }
            if (!isEmpty(&operators) && topChar(&operators) == '(') {
                popChar(&operators); // Pop '('
            }
        }
    }

    while (!isEmpty(&operators)) {
        long val2 = top(&operands);
        pop(&operands);

        long val1 = top(&operands);
        pop(&operands);

        char op = topChar(&operators);
        popChar(&operators);
        push(&operands, applyOp(val1, val2, op));
    }

    // Top of 'values' contains the result, return it.
    return top(&operands);
}

/**
   Function for parsing multiplication and division used to read and evaluate the equation. Calls on parse_exp when seeing one.
   @param express the expression being operated on
   @return a long value.
 */
static long parse_mul_div(char* express)
{
    char* expression;
    expression = skipSpace(express);
    int valid = isValid(expression);
    if(valid != 0)
    {
        puts("yahs fail\n");
        exit(FAIL_INPUT);
    }
    long return_value = parse_exp(expression);
    return return_value;
}

/**
 * Main program that runs and takes input from the terminal to calculate the function.
 * @param argc a argument / equation
 * @param aargv a pointer for infix_n to convert base to the chosen value.
 * @return int that is evaluated and outputted in the chosen base.
*/
int main(int argc, char **argv)
{

    if(strcmp("./infix_10", argv[0]) == 0)
    {
        char expression[MAX_SIZE];
        
        scanf(" %[^\n]", expression);

        long result = parse_mul_div(expression);
       
        printValue(result);
    }

    else if(strcmp("./infix_32", argv[0]) == 0)
    {
        char expression[MAX_SIZE];
        
        scanf(" %[^\n]", expression);
        int operatorsBeforeParse = numberOfOperators(expression);
        char* expression_without_space = malloc(strlen(expression) * sizeof(char));
        expression_without_space = skipSpace(expression);
        int base = 32;

        char* convertedExpression = convertBaseNtoBase10(expression_without_space, base);
        
        int operatorsAfterParse = numberOfOperators(convertedExpression);
        if(operatorsBeforeParse != operatorsAfterParse)
        {
            exit(FAIL_OVERFLOW);
        }
        long result = (long)parse_mul_div(convertedExpression);
        if(result == LONG_MIN)
        {
            printf("%ld\n", LONG_MIN_BASE32);
            return 0;
        }
        
        convertToBase(result, base);

    }
    
    else if(strcmp("./infix_n", argv[0]) == 0)
    {
    char expressionString[MAX_SIZE];
    
    scanf(" %[^\n]", expressionString);

    ExpressionData data = parseExpression(expressionString);

    if (data.expression != NULL) {
        // printf("Base: %d\n", data.base);
        // printf("Expression: %s\n", data.expression);
        int operatorsBeforeParse = numberOfOperators(data.expression);
        char* convertedExpression = convertBaseNtoBase10(data.expression, data.base);
        
        int operatorsAfterParse = numberOfOperators(convertedExpression);
        
        if(operatorsBeforeParse != operatorsAfterParse)
        {
            exit(FAIL_OVERFLOW);
        }
        long result = (long)parse_mul_div(convertedExpression);
        convertToBase(result, data.base);
        free(data.expression);
    }
    }
    else
    {
        puts("please make infix_10 infix_32 infix_n first\n");
    }
    return 0;
}


