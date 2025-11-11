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

// --- NEW VARIABLES FOR PART 2 ---

// A pointer to the encoding key string.
// Default is "0", which means "add 0" -> no change.
// This is a great trick from the instructions!
char *encode_key = "0";

// The current index in the encode_key string
int key_index = 0;

// 1 for addition (+E), -1 for subtraction (-E)
int encode_direction = 1; 

/*
 * ============================================
 * Encoder Function (Full Logic)
 * ============================================
 * This function now implements the cyclic encoding logic.
 */
char encode(char c) {
    // 1. Get the current digit from the key
    char key_char = encode_key[key_index];

    // 2. Check if we reached the end of the key string
    if (key_char == '\0') {
        key_index = 0; // Reset index to the beginning
        key_char = encode_key[key_index]; // Get the first digit
    }

    // 3. Convert the digit char (e.g., '3') to its int value (e.g., 3)
    int shift_value = key_char - '0';

    // 4. IMPORTANT: Advance the key index for the *next* call
    // This happens even if we don't encode the character.
    key_index++;

    // 5. Apply encoding ONLY to 'A'-'Z' or '0'-'9'
    if (c >= 'A' && c <= 'Z') {
        // Apply shift (direction is 1 or -1)
        int shifted_c = c + (shift_value * encode_direction);
        
        // Handle wrap-around
        if (shifted_c > 'Z') {
            c = shifted_c - 26; // 'Z' + 1 becomes 'A'
        } else if (shifted_c < 'A') {
            c = shifted_c + 26; // 'A' - 1 becomes 'Z'
        } else {
            c = shifted_c;
        }
    } 
    else if (c >= '0' && c <= '9') {
        // Apply shift (direction is 1 or -1)
        int shifted_c = c + (shift_value * encode_direction);

        // Handle wrap-around
        if (shifted_c > '9') {
            c = shifted_c - 10; // '9' + 1 becomes '0'
        } else if (shifted_c < '0') {
            c = shifted_c + 10; // '0' - 1 becomes '9'
        } else {
            c = shifted_c;
        }
    }

    // 6. If 'c' was not eligible (e.g., 'a', '#', '\n'),
    // we simply return it unchanged.
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
    for (int i = 1; i < argc; i++) {
        
        // a. Check for "-D" to turn off debug
        if (strcmp(argv[i], "-D") == 0) {
            debug_mode = 0; // Turn off debug
        }
        // b. Check for "+D" to turn on debug (with password)
        else if (strncmp(argv[i], "+D", 2) == 0) {
            if (strcmp(argv[i] + 2, debug_password) == 0) {
                debug_mode = 1; // Turn on debug
            }
        }
        
        // --- NEW CHECKS FOR PART 2 ---

        // c. Check for "+Ekey" (addition)
        else if (strncmp(argv[i], "+E", 2) == 0) {
            encode_key = argv[i] + 2; // The key starts after "+E"
            encode_direction = 1;     // Set direction to addition
        }
        // d. Check for "-Ekey" (subtraction)
        else if (strncmp(argv[i], "-E", 2) == 0) {
            encode_key = argv[i] + 2; // The key starts after "-E"
            encode_direction = -1;    // Set direction to subtraction
        }
        
        // --- End of new checks ---

        // e. If debug mode is on, print the argument to stderr
        if (debug_mode) {
            fprintf(stderr, "Argument: %s\n", argv[i]);
        }
    }

    // 3. "Echo" Loop (Reading and Writing)
    int c; 

    while ((c = fgetc(infile)) != EOF) {
        
        char encoded_c = encode(c); // Call the encode function (now with logic)
        
        fputc(encoded_c, outfile); 
    }
    
    // 4. Close files
    if (infile != stdin)
        fclose(infile);
    if (outfile != stdout)
        fclose(outfile);

    return 0; // Exit program successfully
}