/*
@author: Daniel Yowell
*/

#include <stdio.h>
#include <stdlib.h>

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
        if(min > arr[i]) {
            min = arr[i];
        }
    }
    printf("min: %f\n", min);

/* CONVERT MIN (FLOAT) TO CHAR ARRAY */
char buffer2[64];
int ret = snprintf(buffer2, sizeof buffer2, "%f", min);

if (ret < 0) {
    return EXIT_FAILURE;
}
if (ret >= sizeof buffer) {
    // Result was truncated - resize the buffer and retry.
}

/* WRITE TO OUTPUT FILE */

    //fprintf("Min: %f\n", min);

    // close files and free memory
    fclose(inputFile);
    fclose(outputFile);
    free( buffer );
    free( arr );
    return 0;

}