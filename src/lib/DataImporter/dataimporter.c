#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataimporter.h"

#include <io.h>

// Iterates through the file, counting for each line and for each character
// Storing and returning the amount of lines and the longest counted line
filesize ScanFile(FILE *file, int bufferSize) {
    filesize f;
    f.lineCount = 0;
    f.longestLine = 0;
    char buffer[bufferSize];
    int charCount = 0;
    for(;;) {
        size_t result = fread(buffer, 1, bufferSize, file);
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
            else {
                result[i][j] = 0;
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

// Prints 2d int array
void Print2dArrayINT(int **array, int rows, int columns){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d", array[i][j]);
        }
        printf("\n");
    }
}

// Prints 2d char array
void Print2dArraySTR(char **array, int rows){
    for (int i = 0; i < rows; i++) {
            printf("%s\n", array[i]);
    }
    }

// Prints 2d int array (as colored spaces, 1 = green, 2 = blue)
void Print2dArrayINTColored(int **array, int rows, int columns){
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
void Print2dArrayCHARColored(char **array, int rows, int columns){
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
char **Allocate2dCHARArray(int rows, int columns){
    char **charArray2d = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        charArray2d[i] = malloc((columns + 1) * sizeof(char));
    }
    return charArray2d;
}

// allocates and returns 2d int array
int **Allocate2dINTArray(int rows, int columns){
    int **intArray2d = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        intArray2d[i] = malloc((columns + 1) * sizeof(int));
    }
    return intArray2d;
}

// Reads contents of a file into 2d char array
void ReadFileDataInto2dCHARArray(FILE *file, char **array, int rows, int columns){
    for (int i = 0; i < rows; i++){
        fgets(array[i], columns, file);
        char *newLine = strchr(array[i], '\n');
        if (newLine) {
            *newLine = '\0';
        }
    }
}

void pwd(void) {
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
}