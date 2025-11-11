# C Encoder Utility - Systems Programming Lab A

![Language](https://img.shields.io/badge/Language-C-blue.svg) ![Platform](https://img.shields.io/badge/Platform-Linux%2032--bit-red.svg) ![Compiler](https://img.shields.io/badge/Compiler-GCC-orange.svg) ![Assembler](https://img.shields.io/badge/Assembler-NASM-green.svg) ![Build](https://img.shields.io/badge/Build-Make-yellow.svg)

This project is a C program developed for the "Systems Programming" course. It implements a simple character encoder utility that reads from standard input (or a file), performs a cyclic substitution cipher, and writes to standard output (or a file). The program is built to run in a 32-bit Linux environment and is managed by a `Makefile`.

---

## 🚀 Features

* **Character-by-Character Processing:** Reads and writes one character at a time.
* **Cyclic Substitution Cipher:** Encodes/decodes input using a numeric key (e.g., `+E123` or `-E456`).
* **Selective Encoding:** The cipher only affects uppercase letters (`A-Z`) and digits (`0-9`).
* **Debug Mode:** A toggleable debug mode (`-D`, `+Dpassword`) prints arguments to `stderr`.
* **I/O Redirection:** Supports input from a file (`-ifilename`) and output to a file (`-ofilename`).
* **Argument Parsing:** Handles command-line arguments in any order.

---

## 🛠️ Environment & Requirements

This project is designed for a 32-bit Linux environment. To compile it, you will need:
* `gcc` with 32-bit libraries (`gcc-multilib`)
* `nasm` (The Netwide Assembler)
* `make` utility

---

## ⚙️ Building the Project

First, ensure you have the required tools (see above).

1.  Clone the repository:
    ```bash
    git clone [https://github.com/ReemSchur/system-programming-lab-a.git](https://github.com/ReemSchur/system-programming-lab-a.git)
    cd system-programming-lab-a
    ```
2.  Run `make`:
    ```bash
    make
    ```
    This will build the main executable: `encoder`. It will also build the other programs from Part 0 (`my_program` and `my_echo`).

3.  To build *only* the encoder, run:
    ```bash
    make encoder
    ```
4.  To clean up all built files:
    ```bash
    make clean
    ```

---

## 🖥️ Usage

The program is run from the command line with various flags.

```bash
./encoder [FLAGS]

./encoder
# Type 'Hello' and press Enter. It will echo 'Hello'.
# Press Ctrl+D to exit.

./encoder +E12345
# Input: ABCDEZ
# Output: BDFHJA

echo "TEST 123" > input.txt
./encoder +E1 -iinput.txt -ooutput.txt
cat output.txt
# Output: UFTU 234

./encoder +E1 -D -iinput.txt
# Output to stderr:
# Argument: +E1
# Argument: -D
# Argument: -iinput.txt

./encoder -iFileDoesNotExist.txt
# Output to stderr:
# Error: Could not open input file FileDoesNotExist.txt