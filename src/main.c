#include "header.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    printf("Fucking cLion AAAAAAAAAAAAAAAAAAAAAAAAAA!\n");

    state_t state = construct_state();



    return 0;
}

void error_handling(char *message) {
    printf("%s (press ENTER to end prosess)", message);
    getchar();
    exit(EXIT_FAILURE);
}
