/*
@author: Daniel Yowell
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    char line[1000]; // Adjust the buffer size as needed
    
/* GET INPUT/OUTPUT FILES */
    
    if (argc != 3) {
        fprintf(stderr, "Expected format: %s input#.txt output#.txt\n", argv[0]);
        return 0; // learned the hard way: return 0 for all terminations, not 1, otherwise gcov will throw error
    }

    const char *inputFilePath = argv[1];
    const char *outputFilePath = argv[2];

    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *outputFile = fopen(outputFilePath, "w");

    if (inputFile == NULL || outputFile == NULL) {
        remove(argv[2]); // delete output file if it was created
        perror("Failed to open file");
        return 0;
    }

/* SCAN ROW/COL INFO FROM LINE 1 */

    int num = 0;
    fscanf(inputFile, "%d", &num);
    //printf("rows: %d\n", num);
    int maxRows = num;
    fscanf(inputFile, "%d", &num);
    //printf("cols: %d\n", num);
    int maxCols = num;

    rewind(inputFile);

/* CREATE 2D ARRAY AND READ IN VALUES */

    // dynamically allocate 2D array with dimensions maxRows x maxCols
    int **arr2D = (int **)malloc(maxRows * sizeof(int *));
    for(int i = 0; i < maxRows; i++) {
        arr2D[i] = (int *)malloc(maxCols * sizeof(int));
    }

    // read input file into arr2D
    int row = 0;
    int col = 0;

    // skip first line
    fgets(line, sizeof(line), inputFile);
    // fgets gets each line and stores it in line
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // strtok stands for "string token" (i think) and splits the line into tokens (chars)
        // uses spaces as delimiters, so all multi-digit numbers are preserved
        // strtok returns a pointer to the first token
        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            // isdigit checks if the token is a valid digit
            if (isdigit(token[0])) {
                // atoi converts the token to an int. we then put it in arr2D
                arr2D[row][col] = atoi(token);
                col++;
            }
            // call strtok again to get the next token
            token = strtok(NULL, " \t\n");
        }
        row++;
        col = 0;
    }

/* TRANSPOSE 2D ARRAY */

    // just do everything as before, with maxRows and maxCols switched
    int **transpose = (int **)malloc(maxCols * sizeof(int *));
    for(int i = 0; i < maxCols; i++) {
        transpose[i] = (int *)malloc(maxRows * sizeof(int));
    }

    for (int i = 0; i < maxCols; i++) {
        for (int j = 0; j < maxRows; j++) {
            transpose[i][j] = arr2D[j][i];
        }
    }

/* PRINT TO OUTPUT FILE */

    fprintf(outputFile, "%d %d\n", maxCols, maxRows);
    for(int i = 0; i < maxCols; i++) {
        for(int j = 0; j < maxRows; j++) {
            fprintf(outputFile, "%d ", transpose[i][j]);
        }
        fprintf(outputFile, "\n");
    }

}