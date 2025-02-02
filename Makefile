# Makefile for compiling MPI program

# Compiler and flags
CC = mpicc
CFLAGS = -lm -O3

# Targets
TARGET = p1
SRC = p1.c

# Default rule
all: $(TARGET)

# Compile the MPI program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET) *.o
