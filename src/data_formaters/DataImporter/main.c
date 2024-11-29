#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "test.txt"
#define PACKET_BUF_SIZE 1048576
#define DELIMITER '\n'

typedef struct {
    int lineCount;
    int longestLine;
} filesize;

filesize ScanFile(FILE* file);  // https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file/70708991#70708991 by Mike Siomkin
int** ConvertToInt(char **array, int rows, int columns);
void Free2dArrayINT(int** arr, int rows);
void Free2dArrayCHAR(char** arr, int rows);

int main(void) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    filesize f = ScanFile(file);
    char** dataStruct = malloc(f.lineCount * sizeof(char*));
    for (int i = 0; i < f.lineCount; i++) {
        dataStruct[i] = malloc((f.longestLine + 1) * sizeof(char));
    }
    for (int i = 0; i < f.lineCount; i++){
            fgets(dataStruct[i], f.longestLine+1, file);
            char *delimiterPtr = strchr(dataStruct[i], DELIMITER);
            if (delimiterPtr) {
                *delimiterPtr = '\0';
            }
        }
    fclose(file);
    int** resultArray = ConvertToInt(dataStruct,f.lineCount,f.longestLine);
    for (int i = 0; i < f.lineCount; i++) {
        for (int j = 0; j < f.longestLine; j++) {
            printf("%d ",resultArray[i][j]);
        }
    }
    Free2dArrayCHAR(dataStruct,f.lineCount);
    Free2dArrayINT(resultArray,f.lineCount);

    return 0;
}

filesize ScanFile(FILE* file) {
    filesize f;
    f.lineCount = 0;
    f.longestLine = 0;
    char buf[PACKET_BUF_SIZE];
    int charCount = 0;
    for(;;) {
        size_t res = fread(buf, 1, PACKET_BUF_SIZE, file);
        if (ferror(file)) {
            printf("Error reading file");
            exit(-1);
        }
        for(int i = 0; i < res; i++) {
            charCount++;
            if (buf[i] == '\n') {
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

int** ConvertToInt(char **array, int rows, int columns){
    int** result = malloc(rows * sizeof(int*));
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

void Free2dArrayINT(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

void Free2dArrayCHAR(char** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}



