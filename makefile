# --- Variables ---
CC = gcc
CFLAGS = -Wall -g -m32

ASM = nasm
ASMFLAGS = -f elf32

# --- Targets ---

# Added "encoder" to the default target
all: my_program my_echo encoder

# --- Rules for my_program (unchanged) ---
my_program: main.o numbers.o add.o
	$(CC) $(CFLAGS) -o my_program main.o numbers.o add.o

add.o: add.s
	$(ASM) $(ASMFLAGS) -o add.o add.s

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

numbers.o: numbers.c
	$(CC) $(CFLAGS) -c -o numbers.o numbers.c

# --- Rules for my_echo (unchanged) ---
my_echo: my_echo.c
	$(CC) $(CFLAGS) -o my_echo my_echo.c

# --- Rules for encoder (NEW) ---
# A simple rule that explains how to build encoder
encoder: encoder.c
	$(CC) $(CFLAGS) -o encoder encoder.c

# --- Clean Target ---
# Added "encoder" to the clean list
clean:
	rm -f my_program my_echo encoder *.o