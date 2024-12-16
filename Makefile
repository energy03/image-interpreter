# Makefile

# Compiler
CC = gcc

# Header directory
HEADER = include

# Source directory
SRC = src

# Object directory
OBJ = obj

# Binary directory
BIN = bin

# Flags
OBJFLAGS = -c -I$(HEADER)
CFLAGS = -I$(HEADER)

# Source files dans le répertoire src et ses sous-répertoires
SRCFILES = $(shell find $(SRC) -name "*.c")

# Object files
OBJFILES = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCFILES))

# Binary file
BINFILE = $(BIN)/prog

# Default target
all: $(BINFILE)

# Creating object files with subdirectories
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(OBJFLAGS) $< -o $@

# Linking
$(BINFILE): $(OBJFILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

# Clean
clean:
	rm -rf $(OBJ) $(BIN)

# Run
run:
	$(BINFILE)

# Debug
debug:
	gdb $(BINFILE)

# Valgrind
valgrind:
	valgrind --leak-check=full $(BINFILE)

# Help
help:
	@echo "all: Compile and link the program"
	@echo "clean: Remove object files and binary file"
	@echo "run: Run the program"
	@echo "debug: Run the program in debug mode"
	@echo "valgrind: Run the program with valgrind"
	@echo "help: Display this help"

# Phony targets
.PHONY: all clean run debug valgrind help

# End of Makefile