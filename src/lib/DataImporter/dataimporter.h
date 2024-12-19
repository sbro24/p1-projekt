#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H


typedef struct {
    int lineCount;
    int longestLine;
} filesize;

int **Allocate2dINTArray(int rows, int columns);

void VoidAllocate2dINTArray(int **intArray2d, int rows, int columns);

void ReadFileDataInto2dINTArray(FILE *file, int **array, int grid_y, int grid_x, char *delimiter);

void VoidCopy2dArrayINT(int **array1, int **array2, int rows, int columns);

void InitializeMatrixINT(int **matrix, int rows, int columns);

#endif //DATAIMPORTER_H
