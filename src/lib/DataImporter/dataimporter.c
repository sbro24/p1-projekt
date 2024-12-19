#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataimporter.h"


// allocates and returns 2d int array
int **Allocate2dINTArray(int rows, int columns){
    int **intArray2d = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        intArray2d[i] = malloc((columns + 1) * sizeof(int));
    }
    return intArray2d;
}

void VoidAllocate2dINTArray(int **intArray2d, int rows, int columns) {
    malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        intArray2d[i] = malloc((columns + 1) * sizeof(int));
    }
}

void ReadFileDataInto2dINTArray(FILE *file, int **array, int grid_y, int grid_x, char *delimiter) {
    int rows = 0, cols = 0;
    char line[2048];
    while (fgets(line, sizeof(line), file) && rows < grid_y) {
        cols = 0;
        char *token = strtok(line, delimiter);
        while (token != NULL && cols < grid_x) {
            array[rows][cols] = atoi(token); // Convert string to integer
            token = strtok(NULL, delimiter);    // Move to the next token
            cols++;
        }
        rows++;
    }
    rewind(file);
}

void VoidCopy2dArrayINT(int **array1, int **array2, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array2[i][j] = array1[i][j];
        }
    }
}

void InitializeMatrixINT(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
}