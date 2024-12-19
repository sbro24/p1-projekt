// Iterates through the file, counting for each line and for each character
// Storing and returning the amount of lines and the longest counted line
/*
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
                    f.longestLine = charCount + 1;
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
*/

/*
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
*/

/*
// Frees malloc on 2d int array
void Free2dArrayINT(int **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}
*/

/*
// Frees malloc on 2d char array
void Free2dArrayCHAR(char **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}
*/

/*
// Prints 2d int array
void Print2dArrayINT(int **array, int rows, int columns){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d", array[i][j]);
        }
        printf("\n");
    }
}
*/

/*
// Prints 2d char array
void Print2dArraySTR(char **array, int rows){
    for (int i = 0; i < rows; i++) {
            printf("%s\n", array[i]);
    }
    }
*/

/*
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
*/

/*
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
*/
/*
// allocates and returns 2d char array
char **Allocate2dCHARArray(int rows, int columns){
    char **charArray2d = malloc(rows * sizeof(char*)*4);
    for (int i = 0; i < rows; i++) {
        charArray2d[i] = malloc((columns + 1) * sizeof(char));
    }
    return charArray2d;
}
*/

/*
void ReadFileDataInto2dCHARArray(FILE *file, char **array, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        if (fgets(array[i], columns, file) == NULL) {
            break;
        }
        char *newline = strchr(array[i], '\n');
        if (newline) {
            *newline = '\0';
        }
    }
    rewind(file);
}
*/

/*
void Write2dArrayINT(int **array, int rows, int columns, char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%d ", array[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
*/
/*
void Write2dArrayCHAR(char **array, int rows, int columns, char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%c", array[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
*/

/*
void pwd(void) {
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
}
*/


/*
* // an attempt at handling integers with n digits
int **ConvertToInt(char **array, int rows, int columns){
    int **result = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        result[i] = (int*)malloc(columns * sizeof(int));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (array[i][j] >= '0' && array[i][j] <= '9'){
                int k = j+1;
                int digitCount = 0;
                while(array[i][k] >= '0' && array[i][k] <= '9') {
                    digitCount++;
                    k++;
                }
                char *temp = malloc(digitCount * sizeof(char));
                int tempCount = 0;
                temp[tempCount] = array[i][j];
                tempCount++;
                int l = j+1;
                while(array[i][l] >= '0' && array[i][l] <= '9') {
                    temp[tempCount] = array[i][j+k];
                    k++;
                    tempCount++;
                }
                printf("%d\n", atoi(temp));
                result[i][j] = atoi(temp);
                k = 0;
                digitCount = 0;
                tempCount = 0;
                l = 0;
                free(temp);
 */


/*  for (int i = 0; i < rows; i++){
        fgets(array[i], columns, file);
        char *newline = strchr(array[i], '\n');
        if (newline) {
            *newline = '\0';
            *
 */


/*
*     for (int i = 0; i < rows; i++) {
        if (fgets(array[i], columns, file) == NULL) {
            printf("Error: Failed to read line %d from file.\n", i);
            break;
        }
        char *newline = strchr(array[i], '\n');
        if (newline) {
            *newline = '\0';
        }
    }
}
 */


/* void ReadFileDataInto2dCHARArray(FILE *file, char **array, int rows, int columns) {
    int linecount = 1;
    for (int i = 0; i < rows; i++) {
        fgets(array[i], columns, file);
        printf("line: %d\n%s\n", linecount, array[i]);
        char *newline = strchr(array[i], '\n');
        if (newline) {
            *newline = '\0';
        }
        linecount++;
    }
}*/