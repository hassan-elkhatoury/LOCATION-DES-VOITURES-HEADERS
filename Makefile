# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files
SRC = main.c client.c colors.c 

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
OUT = car_rental_program

# Default target to build the program
all: $(OUT)

# Rule to link object files to create the executable
$(OUT): $(OBJ)
    $(CC) $(OBJ) -o $(OUT)

# Rule to compile .c files into .o object files
%.o: %.c
    $(CC) $(CFLAGS) -c $<

# Clean up the build artifacts
clean:
    rm -f $(OBJ) $(OUT)

# Rule to remove the object files and executable
fclean: clean
    rm -f $(OUT)

# Rule to recompile everything (clean and build)
re: fclean all
