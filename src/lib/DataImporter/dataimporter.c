#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataimporter.h"



/*
// example use
int main(void) {

    FILE *file = open_file(FILE_NAME, 'r');
    filesize f = ScanFile(file);
    char **dataStruct = Allocate2dCHARarray(f.lineCount, f.longestLine);
    ReadFileDataInto2dCHARarray(file, dataStruct, f.lineCount, f.longestLine, '\n');
    fclose(file);
    int **resultArray = ConvertToInt(dataStruct,f.lineCount,f.longestLine);
    Print2dArrayCHAR(dataStruct,f.lineCount,f.longestLine);
    Free2dArrayCHAR(dataStruct,f.lineCount);
    Free2dArrayINT(resultArray,f.lineCount);

    return 0;
}
*/

// Iterates through the file, counting for each line and for each character
// Storing and returning the amount of lines and the longest counted line
filesize ScanFile(FILE *file) {
    filesize f;
    f.lineCount = 0;
    f.longestLine = 0;
    char buffer[PACKET_BUFFER_SIZE];
    int charCount = 0;
    for(;;) {
        size_t result = fread(buffer, 1, PACKET_BUFFER_SIZE, file);
        if (ferror(file)) {
            printf("Error reading file");
            exit(-1);
        }
        for(int i = 0; i < result; i++) {
            charCount++;
            if (buffer[i] == '\n') {
                f.lineCount++;
                if (charCount >= f.longestLine) {
                    f.longestLine = charCount;
                }
                charCount = 0;
            }
        }
        if (feof(file))
            break;
    }
    rewind(file);
    return f;
}

// Takes 2d Char array, copies values into int array as int, returns resulting int array
int **ConvertToInt(char **array, int rows, int columns){
    int **result = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        result[i] = (int*)malloc(columns * sizeof(int));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (array[i][j] >= '0' && array[i][j] <= '9'){
                result[i][j] = array[i][j] - '0';
            }
        }
    }
    return result;
};

// Frees malloc on 2d int array
void Free2dArrayINT(int **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

// Frees malloc on 2d char array
void Free2dArrayCHAR(char **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

// Prints 2d int array (as colored spaces, 1 = green, 2 = blue)
void Print2dArrayINT(int **array, int rows, int columns){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (array[i][j] == 1) {
                printf("\033[42m \033[0m");
            }
            if (array[i][j] == 0) {
                printf("\033[44m \033[0m");
            }
        }
        printf("\n");
    }
}

// Prints 2d char array (as colored spaces, 1 = green, 2 = blue)
void Print2dArrayCHAR(char **array, int rows, int columns){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (array[i][j] == '1') {
                printf("\033[42m \033[0m");
            }
            if (array[i][j] == '0') {
                printf("\033[44m \033[0m");
            }
        }
        printf("\n");
    }
}



// allocates and returns 2d char array
char **Allocate2dCHARarray(int rows, int columns){
    char **charArray2d = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        charArray2d[i] = malloc((columns + 1) * sizeof(char));
    }
    return charArray2d;
}

// Reads contents of a file into 2d char array
void ReadFileDataInto2dCHARarray(FILE *file, char **array, int rows, int columns, char delimiter){
    for (int i = 0; i < rows; i++){
        fgets(array[i], columns+1, file);
        char *delimiterPtr = strchr(array[i], delimiter);
        if (delimiterPtr) {
            *delimiterPtr = '\0';
        }
    }
}