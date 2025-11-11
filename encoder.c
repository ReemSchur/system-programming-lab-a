#include <stdio.h>
#include <string.h> // We need this for strcmp and strncmp

/*
 * ============================================
 * Global Variables
 * ============================================
 */

FILE *infile = NULL;
FILE *outfile = NULL;
int debug_mode = 1;

char *encode_key = "0";
int key_index = 0;
int encode_direction = 1; 

/*
 * ============================================
 * Encoder Function (Full Logic)
 * ============================================
 * (This function is complete from Part 2 - no changes)
 */
char encode(char c) {
    char key_char = encode_key[key_index];

    if (key_char == '\0') {
        key_index = 0;
        key_char = encode_key[key_index];
    }

    int shift_value = key_char - '0';
    key_index++;

    if (c >= 'A' && c <= 'Z') {
        int shifted_c = c + (shift_value * encode_direction);
        if (shifted_c > 'Z') c = shifted_c - 26;
        else if (shifted_c < 'A') c = shifted_c + 26;
        else c = shifted_c;
    } 
    else if (c >= '0' && c <= '9') {
        int shifted_c = c + (shift_value * encode_direction);
        if (shifted_c > '9') c = shifted_c - 10;
        else if (shifted_c < '0') c = shifted_c + 10;
        else c = shifted_c;
    }
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
    char *debug_password = "my_password1";

    // 2. Argument loop
    for (int i = 1; i < argc; i++) {
        
        // a. Debug OFF
        if (strcmp(argv[i], "-D") == 0) {
            debug_mode = 0;
        }
        // b. Debug ON
        else if (strncmp(argv[i], "+D", 2) == 0) {
            if (strcmp(argv[i] + 2, debug_password) == 0) {
                debug_mode = 1;
            }
        }
        // c. Encoder ADD
        else if (strncmp(argv[i], "+E", 2) == 0) {
            encode_key = argv[i] + 2;
            encode_direction = 1;
        }
        // d. Encoder SUBTRACT
        else if (strncmp(argv[i], "-E", 2) == 0) {
            encode_key = argv[i] + 2;
            encode_direction = -1;
        }
        
        // --- NEW CHECKS FOR PART 3 ---
        
        // e. Input file
        else if (strncmp(argv[i], "-i", 2) == 0) {
            char *filename = argv[i] + 2; // Get filename (e.g., "input.txt")
            infile = fopen(filename, "r"); // Open for "reading"
            
            // Error handling
            if (infile == NULL) {
                fprintf(stderr, "Error: Could not open input file %s\n", filename);
                return 1; // Exit with an error
            }
        }
        // f. Output file
        else if (strncmp(argv[i], "-o", 2) == 0) {
            char *filename = argv[i] + 2; // Get filename (e.g., "output.txt")
            outfile = fopen(filename, "w"); // Open for "writing"
            
            // Error handling
            if (outfile == NULL) {
                fprintf(stderr, "Error: Could not open output file %s\n", filename);
                return 1; // Exit with an error
            }
        }
        
        // --- End of new checks ---

        // g. Debug printing (if on)
        if (debug_mode) {
            fprintf(stderr, "Argument: %s\n", argv[i]);
        }
    }

    // 3. "Echo" Loop (Reading and Writing)
    // (No changes needed - this now works with files!)
    int c; 
    while ((c = fgetc(infile)) != EOF) {
        char encoded_c = encode(c);
        fputc(encoded_c, outfile); 
    }
    
    // 4. Close files
    // (This logic is now CRITICAL)
    if (infile != stdin)
        fclose(infile);
    if (outfile != stdout)
        fclose(outfile);

    return 0; // Exit program successfully
}