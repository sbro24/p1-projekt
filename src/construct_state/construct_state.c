#include <stdio.h>
#include <stdlib.h>

#include "construct_state_header.h"
#include "header.h"


state_t construct_state(void) {
    state_t state;

    construct_counties();

    printf("Fucking construct_state AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");
    return state;
}

// opens file with error handling
FILE *open_file(const char *file_name, char mode){
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    return file;
}