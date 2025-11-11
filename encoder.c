#include <stdio.h>
#include <string.h> // We need this for strcmp and strncmp

/*
 * ============================================
 * Global Variables
 * ============================================
 */

// infile: Where to read from. Default: stdin (keyboard)
// outfile: Where to write to. Default: stdout (screen)
FILE *infile = NULL;
FILE *outfile = NULL;

// debug_mode: 1 = on (default), 0 = off.
int debug_mode = 1;

/*
 * ============================================
 * Encoder Function (Skeleton)
 * ============================================
 * For now, this function just returns the character it received
 */
char encode(char c) {
    return c;
}

/*
 * ============================================
 * Main Function
 * ============================================
 */
int main(int argc, char *argv[]) {
    
    // 1. Initialize defaults
    infile = stdin;
    outfile = stdout;

    // This is the hardcoded password required by the assignment
    char *debug_password = "my_password1";

    // 2. Argument loop
    //    Runs from i=1 (the first real argument) to the end of the array
    for (int i = 1; i < argc; i++) {
        
        // a. Check for "-D" to turn off debug
        if (strcmp(argv[i], "-D") == 0) {
            debug_mode = 0; // Turn off debug
        }
        // b. Check for "+D" to turn on debug (with password)
        //    strncmp checks only the first 2 characters
        else if (strncmp(argv[i], "+D", 2) == 0) {
            
            // argv[i] + 2 is a pointer to the start of the password (after +D)
            if (strcmp(argv[i] + 2, debug_password) == 0) {
                debug_mode = 1; // Turn on debug
            }
        }

        // c. If debug mode is on, print the argument to stderr
        //    fprintf works like printf but lets you choose where to print
        //    stderr is the "stream" for errors/debug info
        if (debug_mode) {
            fprintf(stderr, "Argument: %s\n", argv[i]);
        }
    }

    // 3. "Echo" Loop (Reading and Writing)
    int c; // IMPORTANT: int, not char, so it can hold the EOF value

    // fgetc(infile) reads one character from infile
    // The loop runs as long as the character read is not EOF (End Of File)
    while ((c = fgetc(infile)) != EOF) {
        
        char encoded_c = encode(c); // Call the encode function (which does nothing yet)
        
        // fputc(char, file) writes one character to outfile
        fputc(encoded_c, outfile); 
    }
    
    // 4. Close files (not critical now, but required for Part 3)
    if (infile != stdin)
        fclose(infile);
    if (outfile != stdout)
        fclose(outfile);

    return 0; // Exit program successfully
}