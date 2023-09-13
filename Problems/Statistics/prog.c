/*
@author: Daniel Yowell
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

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

    // read the integer in the first line of inputFile
    char initialVal[256];
    if(fgets(initialVal, sizeof(initialVal), inputFile) == NULL) {
        perror("Error 2");
        fclose(inputFile);
        return 0;
    }

    // convert initialVal to intVal
    int intVal;
    if(sscanf(initialVal, "%d", &intVal) != 1) {
        perror("Error 3");
        fclose(inputFile);
        return 0;
    }

    // each line of inputFile contains a float. read each line into a buffer, convert to float, and store in array
    char *buffer = (char* )malloc( 80 );
    size_t len = 0;
    ssize_t read;

    // second buffer may be redundant but I'm not sure how to reuse the first one
    float *arr = (float *)malloc(intVal * sizeof(float));

    // print contents of buffer
    size_t sizeValue = (size_t)intVal;
    for (int i = 0; i < intVal; i++) {
            read = getline(&buffer, &sizeValue, inputFile);
            char *ptr;
            float fval = strtof(buffer, &ptr);
            arr[i] = fval;
    }
    
/* FIND MIN OF ARR */
    float min = arr[0];
    for (int i = 1; i < intVal; i++) {
        if(min >= arr[i]) {
            min = arr[i];
        }
    }
    // printf("min: %f\n", min);
/* FIND MAX OF ARR */
    float max = arr[0];
    for (int i = 1; i < intVal; i++) {
        if(max <= arr[i]) {
            max = arr[i];
        }
    }
    // printf("max: %f\n", max);
/* FIND MEAN OF ARR */
    float mean = 0;
    for (int i = 0; i < intVal; i++) {
        mean = mean + arr[i];
    }
    mean = mean / intVal;
    // printf("mean: %f\n", mean);
/* FIND STANDARD DEVIATION */
    float std = 0;
    // 2. iterate through arr:
    //    - subtract mean from each element
    //    - square result
    //    - add to std
    for (int i = 0; i < intVal; i++) {
        std = std + (arr[i] - mean) * (arr[i] - mean);
    }
    // 3. divide by # of elements
    std = std / intVal;
    // 4. take square root
    std = sqrtf(std);
    // printf("std: %f\n", std);

/* CONVERT MIN (FLOAT) TO CHAR ARRAY */
char buffer2[64];
int ret = snprintf(buffer2, sizeof buffer2, "%f", min);

if (ret < 0) {
    // return EXIT_FAILURE; // will we ever need this?
}
if (ret >= sizeof buffer) {
    // Result was truncated - resize the buffer and retry.
}

/* WRITE TO OUTPUT FILE */

    // Write the float value to the file
    fprintf(outputFile, "Min: %.1f\n", min);
    fprintf(outputFile, "Max: %.1f\n", max);
    fprintf(outputFile, "Avg: %.1f\n", mean);
    fprintf(outputFile, "Std: %f\n", std);

    // close files and free memory
    fclose(inputFile);
    fclose(outputFile);
    free( buffer );
    free( arr );
    return 0;

}