#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H



typedef struct {
    int lineCount;
    int longestLine;
} filesize;

filesize ScanFile(FILE *file, int bufferSize);
int **ConvertToInt(char **array, int rows, int columns);
void Free2dArrayINT(int **array, int rows);
void Free2dArrayCHAR(char **array, int rows);
void Write2dArrayINT(int **array, int rows, int columns, char *filename, char *mode);
void Write2dArrayCHAR(char **array, int rows, int columns, char *filename, char *mode);
void Print2dArrayINT(int **array, int rows, int columns);
void Print2dArraySTR(char **array, int rows);
void Print2dArrayINTColored(int **array, int rows, int columns);
void Print2dArrayCHARColored(char **array, int rows, int columns);
char **Allocate2dCHARArray(int rows, int columns);
int **Allocate2dINTArray(int rows, int columns);
void VoidAllocate2dINTArray(int **intArray2d, int rows, int columns);
void ReadFileDataInto2dCHARArray(FILE *file, char **array, int rows, int columns);
void ReadFileDataInto2dINTArray(FILE *file, int **array, int grid_y, int grid_x, char *delimiter);
void pwd(void);

#endif //DATAIMPORTER_H
