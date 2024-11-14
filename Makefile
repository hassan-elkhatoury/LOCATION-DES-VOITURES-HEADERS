# Compiler and flags 
CC = gcc
CFLAGS = -Wall -g

# Source files
SRC = main.c client.c colors.c connexion.c display_mod.c frst_menu.c interface.c

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
OUT = program.exe

# Default target to build and run the program
all: $(OUT)
	./$(OUT)

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
