# --- Variables ---
# CC: C Compiler
CC = gcc
# CFLAGS: Flags for the C compiler (-m32 for 32-bit)
CFLAGS = -Wall -g -m32

# ASM: Assembler (Netwide Assembler)
ASM = nasm
# ASMFLAGS: Flags for the assembler
# -f elf32 tells nasm to create a 32-bit ELF object file (for Linux)
ASMFLAGS = -f elf32

# --- Targets ---

# Default target: "all"
# Builds both programs
all: my_program my_echo

# --- Rules for my_program ---

# 'my_program' now depends on add.o (the *object* file), not add.s
my_program: main.o numbers.o add.o
	# This rule links all the .o files together
	$(CC) $(CFLAGS) -o my_program main.o numbers.o add.o

# NEW RULE: How to build add.o from add.s
# This rule tells 'make' to use 'nasm' to assemble add.s
add.o: add.s
	# This command uses nasm to assemble add.s into add.o
	$(ASM) $(ASMFLAGS) -o add.o add.s

# Rule for main.o
main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

# Rule for numbers.o
numbers.o: numbers.c
	$(CC) $(CFLAGS) -c -o numbers.o numbers.c

# --- Rules for my_echo ---
my_echo: my_echo.c
	$(CC) $(CFLAGS) -o my_echo my_echo.c

# --- Clean Target ---
# *.o will automatically clean up add.o, main.o, and numbers.o
clean:
	rm -f my_program my_echo *.o