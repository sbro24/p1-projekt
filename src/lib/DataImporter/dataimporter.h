#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H

#define PACKET_BUFFER_SIZE 1048576
#include <stdio.h>

typedef struct {
    int lineCount;
    int longestLine;
} filesize;

filesize ScanFile(FILE *file);  // https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file/70708991#70708991 by Mike Siomkin
int **ConvertToInt(char **array, int rows, int columns);
void Free2dArrayINT(int **array, int rows);
void Free2dArrayCHAR(char **array, int rows);
void Print2dArrayINT(int **array, int rows, int columns);
void Print2dArrayCHAR(char **array, int rows, int columns);
char **Allocate2dCHARarray(int rows, int columns);
void ReadFileDataInto2dCHARarray(FILE *file, char **array, int rows, int columns, char delimiter);

#endif //DATAIMPORTER_H
