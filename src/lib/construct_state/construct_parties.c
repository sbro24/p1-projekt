#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


void construct_party_array(char parties[MAX_NUMBER_OF_PARTIES][4]) {
    //Open the county file specified in "header.h"
    FILE* file = open_file(FILE_COUNTIES, "r");

    //Declare a array of strings that's 4 characters long, E.g. {"D","E","M","\0"} (Party code + End char)
    char party_result[MAX_NUMBER_OF_PARTIES][4] = {""};

    get_unique_parties(file, party_result);

    //copy all the unique party codes into the string array parties specified in the function arguments
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) strcpy(parties[i], party_result[i]);

    fclose(file);
}

void get_unique_parties(FILE* file, char parties[MAX_NUMBER_OF_PARTIES][4]) {
    //reset file pointer
    rewind(file);
    //skip first line
    fscanf(file, "%*[^\n]\n");

    char scanned_party[4];
    //list of unique parties found so far
    char scanned_parties[MAX_NUMBER_OF_PARTIES][4] = {""};

    //loop through file until end
    while (feof(file) == 0) {
        //Scan line, for Party (* ignore)
        fscanf(file, "%*i \t %*[^\t] \t %*i \t %s \t %*i\n", &scanned_party);

        //Count unique parties found so far
        int number_of_parties = count_parties(scanned_parties);

        //check if there's space in scanned_parties
        if (number_of_parties > MAX_NUMBER_OF_PARTIES) error_handling("Maximum number of parties exceeded");

        //continue if scanned_party is not unique
        if (is_string_in_array_of_strings(scanned_parties, scanned_party, number_of_parties)) continue;

        //Copy the unique scanned_party into the next available element
        strcpy(scanned_parties[number_of_parties], scanned_party);
    }
    //copy the result out of the function
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) strcpy(parties[i], scanned_parties[i]);
}

//checks if string is in strings[]
int is_string_in_array_of_strings(char parties[MAX_NUMBER_OF_PARTIES][4], char to_find[], int string_length) {
    int result = 0;
    for (int i = 0; i < string_length; i++) {
        if (!strcmp(parties[i], to_find)) {
            result = 1;
            break;
        }
    }
    return result;
}

//counts how many elements in a string array if it contains 1 or more chars
int count_parties(char parties[MAX_NUMBER_OF_PARTIES][4]) {
    int number_of_parties = 0;
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        if (strlen(parties[i]) == 0) continue;
        number_of_parties++;
    }
    return number_of_parties;
}