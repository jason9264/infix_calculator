CC = gcc
CFLAGS = -c -g -Wall
OFLAGS = -o

# Defines object file dependencies
OBJ = infix.o number_10.o operation.o

# Default target
all: infix_10 infix_32 infix_n

# Rule to create infix_10
infix_10: $(OBJ)
	$(CC) $(OFLAGS) infix_10 $(OBJ)

# Rule to create infix_32
infix_32: infix.o number_32.o operation.o
	$(CC) $(OFLAGS) infix_32 infix.o number_32.o operation.o

# Rule to create infix_n
infix_n: infix.o number_n.o operation.o
	$(CC) $(OFLAGS) infix_n infix.o number_n.o operation.o

# Rule to compile infix.o
infix.o: infix.c number.h operation.h
	$(CC) $(CFLAGS) infix.c

# Rule to compile number_10.o
number_10.o: number_10.c number.h
	$(CC) $(CFLAGS) number_10.c

# Rule to compile number_32.o
number_32.o: number_32.c number.h
	$(CC) $(CFLAGS) number_32.c

# Rule to compile number_n.o
number_n.o: number_n.c number.h
	$(CC) $(CFLAGS) number_n.c

# Rule to compile operation.o
operation.o: operation.c operation.h
	$(CC) $(CFLAGS) operation.c

# Rule to clean the project
clean:
	rm -f infix_10 infix_32 infix_n $(OBJ)

