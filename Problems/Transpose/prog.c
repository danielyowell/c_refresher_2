/*
@author: Daniel Yowell
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int countIntegersInLine(char *line) {
    int count = 0;
    char *token = strtok(line, " \t\n"); // Split the line into tokens using space, tab, and newline as delimiters
    
    while (token != NULL) {
        if (isdigit(token[0])) { // Check if the token is an integer
            count++;
        }
        token = strtok(NULL, " \t\n"); // Get the next token
    }
    
    return count;
}

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

    // count rows
    int maxRows = 0;
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        maxRows++;
    }
    printf("# of rows: %d\n", maxRows);

    rewind(inputFile);

    int maxCols = 0;
    // count columns
    int totalIntegers = 0;
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        totalIntegers = countIntegersInLine(line);
        printf("totalIntegers: %d\n", totalIntegers);
        if(totalIntegers > maxCols) {
            maxCols = totalIntegers;
        }
    }
    printf("max cols: %d\n", maxCols);

    rewind(inputFile);

    // dynamically allocate 2D array with dimensions maxRows x maxCols
    int **matrix = (int **)malloc(maxRows * sizeof(int *));
    for(int i = 0; i < maxRows; i++) {
        matrix[i] = (int *)malloc(maxCols * sizeof(int));
    }

    // read input file into matrix
    int row = 0;
    int col = 0;

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char *token = strtok(line, " \t\n"); // Split the line into tokens using space, tab, and newline as delimiters
        while (token != NULL) {
            if (isdigit(token[0])) { // Check if the token is an integer
                matrix[row][col] = atoi(token);
                col++;
            }
            token = strtok(NULL, " \t\n"); // Get the next token
        }
        row++;
        col = 0;
    }

    // print matrix
    printf("matrix:\n");
    for(int i = 0; i < maxRows; i++) {
        for(int j = 0; j < maxCols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // transpose matrix
    int **transpose = (int **)malloc(maxCols * sizeof(int *));
    for(int i = 0; i < maxCols; i++) {
        transpose[i] = (int *)malloc(maxRows * sizeof(int));
    }

    for (int i = 0; i < maxCols; i++) {
        for (int j = 0; j < maxRows; j++) {
            transpose[i][j] = matrix[j][i]; // Swap row and column indices
        }
    }

    // print transpose
    printf("transpose:\n");
    for(int i = 0; i < maxCols; i++) {
        for(int j = 0; j < maxRows; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }

}