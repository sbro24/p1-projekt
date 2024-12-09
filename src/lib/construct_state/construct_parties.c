#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


void construct_party_array(char parties[MAX_NUMBER_OF_PARTIES][4]) {
    printf("Fucking construct_party_array AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");

    FILE* file = open_file(FILE_COUNTIES, "r");

    char party_result[MAX_NUMBER_OF_PARTIES][4] = {""};
    get_unique_parties(file, party_result);

    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) strcat(parties[i], party_result[i]);

    fclose(file);
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
        fscanf(file, "%*i \t %*[^\t] \t %*i \t %s \t %*i\n", &scanned_party);

        //Count unique parties found so far
        int number_of_parties = count_parties(scanned_parties);

        //continue if scanned_party is not unique
        if (is_party_in_parties(scanned_parties, scanned_party, number_of_parties)) continue;

        strcat(scanned_parties[number_of_parties], scanned_party);

    }
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) strcat(parties[i], scanned_parties[i]);
}

int is_party_in_parties(char parties[MAX_NUMBER_OF_PARTIES][4], char to_find[], int string_length) {
    int result = 0;

    for (int i = 0; i < string_length; i++) {
        if (!strcmp(parties[i], to_find)) {
            result = 1;
            break;
        }
    }
    return result;
}

int count_parties(char parties[MAX_NUMBER_OF_PARTIES][4]) {
    int number_of_parties = 0;
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        if (strlen(parties[i]) == 0) continue;
        number_of_parties++;
    }
    return number_of_parties;
}