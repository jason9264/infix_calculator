Infix Calculator

This program evaluates mathematical expressions provided in infix notation. It supports base 10 (decimal), base 32, and custom bases (n). The program can parse and compute these expressions, handling standard arithmetic operations and parentheses for grouping.

Features

	•	Base 10 Calculation: Evaluates expressions in decimal (base 10) notation.
	•	Base 32 Calculation: Evaluates expressions in base 32 notation.
	•	Custom Base Calculation: Allows evaluation of expressions in any custom base.

Files

	•	infix.c: The main source file containing the logic for parsing and evaluating infix expressions.
	•	number.h: Header file likely containing number-related utility functions.
	•	operation.h: Header file likely containing operation-related utility functions and definitions.

Functions

Main Functions

	•	int main(int argc, char **argv): Entry point of the program. Depending on the executable name (infix_10, infix_32, or infix_n), it reads an expression from standard input and computes the result in the specified base.

Parsing and Evaluation Functions

	•	static long parse_exp(char* expression): Parses and evaluates expressions containing exponents. Utilizes stacks for operands and operators to handle the evaluation.
	•	static long parse_mul_div(char* express): Parses and evaluates expressions containing multiplication and division. Calls parse_exp to handle exponents.

Utility Functions

	•	initializeStack(Stack *stack, int type): Initializes a stack for operands or operators.
	•	isOperator(char ch): Checks if a character is a valid operator.
	•	precedence(char op): Returns the precedence of an operator.
	•	applyOp(long a, long b, char op): Applies an operator to two operands.
	•	parseValue(char* expression, int* index): Parses a numerical value from the expression.
	•	skipSpace(char* expression): Removes spaces from the expression.
	•	isValid(char* expression): Validates the expression format.
	•	numberOfOperators(char* expression): Counts the number of operators in the expression.
	•	convertBaseNtoBase10(char* expression, int base): Converts an expression from a custom base to base 10.
	•	convertToBase(long value, int base): Converts a value from base 10 to a specified base.

Usage

Compile the program:
	•	gcc -o infix_10 infix.c -D BASE=10
	•	gcc -o infix_32 infix.c -D BASE=32
	•	gcc -o infix_n infix.c -D BASE=n


Run the executable:


		For base 10:
	•	./infix_10


		For base 32:
	•	./infix_32


		For custom base:
	•	./infix_n

Input the expression: Enter the expression when prompted. The program will output the evaluated result.


./infix_10
	Enter expression: (3 + 5) * 2
	Result: 16

./infix_32
	Enter expression: (1Z + 1F) * 2
	Result: 82

./infix_n
	Enter expression: base=16; expression=(A + 5) * 2
	Result: 1E

Error Handling

The program checks for invalid expressions and will exit with an error message if an invalid expression is encountered.
Overflow checks are performed when converting between bases to ensure the integrity of the expression.










