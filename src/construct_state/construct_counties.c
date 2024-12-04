#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <unistd.h>
#include "header.h"



void construct_counties(void) {
    printf("Fucking construct_counties AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");

    FILE* file = open_file(FILE_COUNTIES, "r");

    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    get_unique_parties(file, parties);

    //Count number of parties
    int number_of_parties = 0;
    for (int i = 0; i < sizeof(parties) / sizeof(parties[0]); i++) {
        if (strlen(parties[i]) == 0) continue;
        number_of_parties++;
    }

    printf("Number of parties: %d\n", number_of_parties);



}

void get_unique_parties(FILE* file, char parties[MAX_NUMBER_OF_PARTIES][4]) {
    //reset file pointer
    rewind(file);
    //skip first line
    fscanf(file, "%*[^\n]\n");


    char scanned_party[4];
    char scanned_parties[MAX_NUMBER_OF_PARTIES][4] = {""};

    //loop through file until end
    while (feof(file) == 0) {
        //Scan line, for Party
        fscanf(file, "%*[^\t] \t %*i \t %s \t %*i\n", &scanned_party);

        //Count unique parties found so far
        int number_of_parties = 0;
        for (int i = 0; i < sizeof(scanned_parties) / sizeof(scanned_parties[0]); i++) {
            if (strlen(scanned_parties[i]) == 0) continue;
            number_of_parties++;
        }

        //continue if scanned_party is not unique
        if (is_string_in_array(scanned_parties, scanned_party, number_of_parties)) continue;

        strcat(scanned_parties[number_of_parties], scanned_party);

    }
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) strcat(parties[i], scanned_parties[i]);
}

int is_string_in_array(char string[MAX_NUMBER_OF_PARTIES][4], char to_find[], int string_length) {
    int result = 0;

    for (int i = 0; i < string_length; i++) {
        if (!strcmp(string[i], to_find)) {
            result = 1;
            break;
        }
    }
    return result;
}
