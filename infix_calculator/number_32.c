/** 
 * @file number_32.c
 * @author Jason Wang
 * This program calculates and parses input values. The functions are called by functions in infix files for base 32.
*/
#include "number.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"

// Value of the base, so we don't have to use a magic number all over the code. You might need to change this for number_n file.
int BASE = 32;

/**
 * This function reads characters from standard input. It keeps reading characters until it reaches a non-whitespace character or EOF. 
 * It returns the code for the first non-whitespace character it finds (or EOF). For this function, whitespace does not include the newline character. 
 * Code inside the number component or elsewhere in the program can use this to easily skip past whitespace within an expression.
 * @return char code for the first non-whitespace character it finds
*/
char* skipSpace(char* expression)
{
    char* result = expression;
    char* current = expression;

    while (*current) {
        if (!isspace(*current)) {
            *result = *current;
            result++;
        }
        current++;
    }

    *result = '\0';  // Null-terminate the resulting string
    return expression;
}

/**
 * This function reads the next number from the input.it will read a number in base 32
 * If it detects errors in the input number, it terminates the program with the appropriate exit status.
 * @param expression the expression to read
 * @param i the integer array space
 * @return long value the parsed value as base value.
*/
long parseValue(char* expression, int* i)
{
    long val = 0;
    int expression_length = strlen(expression);
    while (*i < expression_length && isdigit(expression[*i])) 
    {
        val = (val * 10) + (expression[*i] - '0');
        *i = *i + 1;
    }
    return val;
}


/**
 * This function prints the given val to standard output calls on the recursive function to print.. 
 * @param val the value to print as.
*/
void printValue(long val)
{
    printf("%ld", val);
}

/**
 * This function converts the digit to base 10. 
 * @param digit the digit read in.
 * @param base the base to convert digit to
 * @return long value converted
*/
long convertDigitToBase10(char digit, int base) 
{
    long value;

    // Check for invalid characters
    if (digit >= '0' && digit <= '9') {
        value = digit - '0';
    } else if (digit >= 'A' && digit <= 'Z') {
        value = digit - 'A' + 10;
    } else {
        printf("Invalid character: %c\n", digit);
        exit(FAIL_INPUT);
    }

    // Check for invalid digits in base N
    if (value >= base) {
        exit(FAIL_INPUT);
    }

    return value;
}

/**
 * This function converst base N to base 10 for more conversion
 * @param expression the const expression
 * @param base the base to be used
 * @return char* the char to be as base 10
*/
char* convertBaseNtoBase10(const char* expression, int base) 
{
    int len = strlen(expression);
    char* convertedExpression = malloc((len * 2 + 1) * sizeof(char));  // Allocate memory for the converted expression
    int convertedIndex = 0;

    for (int i = 0; i < len; i++) {
        // Check if the character is a valid digit in base N
        if ((expression[i] >= '0' && expression[i] <= '9') || (expression[i] >= 'A' && expression[i] <= 'Z')) {
            int startIndex = i;
            int endIndex = i;

            // Find the end index of the number
            while (endIndex < len && ((expression[endIndex] >= '0' && expression[endIndex] <= '9') || (expression[endIndex] >= 'A' && expression[endIndex] <= 'Z'))) {
                endIndex++;
            }

            // Convert the number to base 10
            long value = 0;
            long power = 1;
            for (int j = endIndex - 1; j >= startIndex; j--) {
                long digitValue = convertDigitToBase10(expression[j], base);
                value += digitValue * power;
                power *= base;
            }

            // Convert the value to a string and append it to the converted expression
            char valueString[20];  // Assuming the maximum number of digits is 20
            sprintf(valueString, "%ld", value);
            strcat(convertedExpression, valueString);
            convertedIndex += strlen(valueString);

            // Update the main loop index
            i = endIndex - 1;
        } else {
            // Append the operator to the converted expression
            convertedExpression[convertedIndex] = expression[i];
            convertedIndex++;
        }
    }

    convertedExpression[convertedIndex] = '\0';  // Null-terminate the converted expression

    return convertedExpression;
}

/**
 * Function to check if a character is a valid digit in the given base
 * @param digit the digit to check if valid
 * @param base the base to check the digit WITH
 * @return an int value if valid as a result.
 */
int isValidDigit(int digit, int base) {
    if (base <= 10) {
        return (digit >= 0 && digit < base);
    } else
     {
        return (digit >= 0 && digit <= 9) || (digit >= 10 && digit < base);
    }
}

/**
 * Function to convert a decimal value to the specified base
 * @param val the value to convert
 * @param base the base to convert value to
 */ 
void convertToBase(long val, int base) {
    if (base < 1 || base > 32) {
        
        exit(FAIL_INPUT);
    }

    int result[100];
    int i = 0;

    if (val == 0) {
        result[i++] = 0;
    } else {
        int negative = 0;

        if (val < 0) {
            negative = 1;
            val = -val;
        }

        while (val > 0) {
            int remainder = val % base;
            result[i++] = remainder;
            val /= base;
        }

        if (negative) {
            result[i++] = -1; // Flag for negative sign
        }
    }
    if (i == 0) {
        printf("0");
    } else {
        if (result[i - 1] == -1) {
            printf("-");
            i--;
        }

        for (int j = i - 1; j >= 0; j--) {
            if (result[j] < 10) {
                printf("%d", result[j]);
            } else {
                printf("%c", 'A' + result[j] - 10);
            }
        }
    }

    printf("\n");
}

/**
 * Figures out the total number of operators
 * @param expression the expression so it can count the number of operatiors.
*/
int numberOfOperators(char* expression)
{
    int total_num_of_operators = 0;
    int expression_length = strlen(expression);
    for(int i = 0; i < expression_length;i++)
    {
        if(isOperator(expression[i]))
        {
            total_num_of_operators++;
        }
    }

    return total_num_of_operators;

}

/**
 * Parses expression string, extracts base value and expression.
 * @param expressionString expression string to be parsed
 * @return ExpressionData structure containing extracted base value  expression.
 */
ExpressionData parseExpression(const char* expressionString) {
    ExpressionData data;

    // Create a copy of the expression string
    char expressionCopy[MAX_SIZE];
    strcpy(expressionCopy, expressionString);

    // Tokenize the expression copy using space as the delimiter
    char* token = strtok(expressionCopy, " ");

    // Extract the base value
    if (token == NULL || sscanf(token + 1, "%d", &data.base) != 1) {
        printf("Error: Invalid base value in the expression.\n");
        data.base = 0;
        data.expression = NULL;
        return data;
    }

    // Tokenize further to get the complete expression
    char expressionBuffer[MAX_SIZE] = "";
    token = strtok(NULL, "");
    if (token == NULL) {
        printf("Error: Expression missing in the input.\n");
        data.base = 0;
        data.expression = NULL;
        return data;
    }

    // Remove leading and trailing spaces from the expression
    const char* expressionStart = token;
    while (*expressionStart == ' ') {
        expressionStart++;
    }
    int expressionLength = strlen(expressionStart);
    while (expressionLength > 0 && expressionStart[expressionLength - 1] == ' ') {
        expressionLength--;
    }

    // Copy the expression into the buffer
    strncpy(expressionBuffer, expressionStart, expressionLength);
    expressionBuffer[expressionLength] = '\0';

    // Allocate memory for the expression and copy it
    data.expression = malloc(strlen(expressionBuffer) + 1);
    strcpy(data.expression, expressionBuffer);

    return data;
}
