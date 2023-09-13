/*
@author: Daniel Yowell
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

/* array to store the occurrences of lowercase letters */
    int letterCount[26] = {0}; // One element for each letter (a to z)

/* GET INPUT/OUTPUT FILES */
    
    if (argc != 3) {
        fprintf(stderr, "Expected format: %s input#.txt output#.txt\n", argv[0]);
        return 0; // learned the hard way: return 0 for all terminations, not 1, otherwise gcov will throw error
    }

    const char *inputFilePath = argv[1];
    const char *outputFilePath = argv[2];

    FILE *inputFile = fopen(inputFilePath, "r+");
    FILE *outputFile = fopen(outputFilePath, "w");

    if (inputFile == NULL || outputFile == NULL) {
        remove(argv[2]); // delete output file if it was created
        perror("Failed to open file");
        return 0;
    }

     // Read characters from the file until EOF is reached
    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (c >= 'a' && c <= 'z') {
            letterCount[c - 'a']++;
        }
    }

/* PRINT */
    for(int i = 0; i < 26; i++) {
        // printf("%c: %d\n", 'a' + i, letterCount[i]);
        //fprintf(outputFile, "%c: %d\n", 'a' + i, letterCount[i]);
    }

/* next:
in a while loop, iterate through letterCount and fprint a space if 0
also display in console
*/
int allZero = 0;
// repeat until allZero == 1
while(allZero == 0) {
    // set allZero to  1
    allZero = 1;
    fprintf(outputFile, "\n");
    printf("\n");
    for(int i = 0; i < 26; i++) {
        if(letterCount[i] > 0) {
            // if there is a nonzero value (a letter), set allZero to 0
            allZero = 0;
            fprintf(outputFile, "X");
            printf("X");
            letterCount[i] = letterCount[i] - 1;
        }
        else {
            fprintf(outputFile, " ");
            printf(" ");
        }    
    }
    rewind(outputFile);
}

    

    fclose(inputFile);
    fclose(outputFile);
    return 0;

}