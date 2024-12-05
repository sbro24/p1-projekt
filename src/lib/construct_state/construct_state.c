#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "construct_state_header.h"
#include "header.h"


state_t construct_state(void) {
    state_t state;

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
        char error_message[256] = "Couldn't open ";
        strcat(error_message, path);
        error_handling(error_message);
    }
    return file;
}

int count_counties_in_struct(county_t counties[MAX_NUMBER_OF_COUNTIES]) {
    int number_of_counties = 0;
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        if (strlen(counties[i].name) == 0) continue;
        number_of_counties++;
    }
    return number_of_counties;
}