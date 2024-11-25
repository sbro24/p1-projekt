#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "test.txt"
#define PACKET_BUF_SIZE 1048576

struct filesize {
    int lineCount;
    int longestLine;
};

struct filesize ScanFile(FILE* file);  // https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file/70708991#70708991 by Mike Siomkin
void printData(char data[]);

int main(void) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    struct filesize f = ScanFile(file);
    char dataStruct[f.lineCount][f.longestLine];
    for (int i = 0; i < f.lineCount; i++){
            fgets(dataStruct[i], f.longestLine+1, file);
            char *newline = strchr(dataStruct[i], '\n');
            if (newline) {
                *newline = '\0';
            }
            printf("%s\n", dataStruct[i]);
        }
    fclose(file);
    return 0;
}

struct filesize ScanFile(FILE* file) {
    struct filesize f;
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
