#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "construct_state_header.h"
#include "header.h"


state_t construct_state(void) {
    state_t state;

    construct_counties();

    printf("Fucking construct_state AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");
    return state;
}

// opens file with error handling
FILE *open_file(const char *file_name, const char *mode){
    int str1 = strlen(INPUT_DIRECTORY);
    int str2 = strlen(file_name);
    char path[str1 + str2 + 1];
    strcpy(path, INPUT_DIRECTORY);
    strcat(path, "/");
    strcat(path, file_name);
    FILE *file = fopen(path, mode);
    if (file == NULL) {
        printf("%s not found (press ENTER to close)", path);
        getchar();
        exit(EXIT_FAILURE);
    }
    return file;
}