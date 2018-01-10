# MACRO definitions
CC = gcc
CFLAG = -std=c99 -Wall

# All Targets
all: operation

# operation depends on the files operation.o and operation_functions.o
operation: operation.o operation_functions.o 
	$(CC) $(CFLAG) -o operation operation.o operation_functions.o

# operation.o depends on the source and header files
operation.o: operation.c operation_functions.h
	$(CC) $(CFLAG) -c operation.c

# operation_functions.o depends on the source and header files
operation_functions.o: operation_functions.c operation_functions.h
	$(CC) $(CFLAG) -c operation_functions.c

#clean the build inventory
clean:
	rm -f *.o operation

#test operation with values 1 2 3 4
test: operation
	operation 1 2 3 4 > output_file
