#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <unistd.h>
#include "header.h"



void construct_counties(void) {
    printf("Fucking construct_counties AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");

    FILE* file = open_file(FILE_COUNTIES, "r");

    int number_of_parties = calc_number_of_parties(file);
    printf("Number of parties: %d\n", number_of_parties);



}

int calc_number_of_parties(FILE* file) {
    //reset file pointer
    rewind(file);
    //skip first line
    fscanf(file, "%*[^\n]\n");


    char scaned_party[4];
    char scaned_parties[MAX_NUMBER_OF_PARTIES][4];

    //loop through file until end
    while (feof(file) == 0) {
        //Scan line, for Party
        fscanf(file, "%[^\t] \t %*i \t %[^\t] \t %*i\n", &scaned_party);
    }

    return 10000;
}