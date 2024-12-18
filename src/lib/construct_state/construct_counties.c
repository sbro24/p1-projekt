#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* constructs an array of all the counties with data form the input file
* @param array where the results are inputed
* @param a list with all the unique parties codes
* @param int of how many unique parties codes there are
* @return void
*/
void construct_county_array(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {
    //Open the county file specified in "header.h"
    FILE* file = open_file(FILE_COUNTIES, "r");

    //copy the list of parties in a new array
    char parties_copy[MAX_NUMBER_OF_PARTIES][4] = {""};
    for (int i = 0; i < number_of_parties; i++) strcpy(parties_copy[i], parties[i]);

    //declare the array of structs and make all the fields empty or 0
    county_t county_results[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};;

    get_unique_counties(file, county_results, parties_copy, number_of_parties);

    //copy all the results into county_t counties specified in the function arguments
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        counties[i].index = county_results[i].index;
        strcpy(counties[i].name, county_results[i].name);
        counties[i].district = county_results[i].district;
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) counties[i].votes[j] = county_results[i].votes[j];
    }

    fclose(file);
}

void get_unique_counties(FILE* file, county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {
    //reset file pointer
    rewind(file);
    //skip first line
    fscanf(file, "%*[^\n]\n");

    //copy parties
    char parties_copy[MAX_NUMBER_OF_PARTIES][4] = {""};
    for (int i = 0; i < number_of_parties; i++) strcpy(parties_copy[i], parties[i]);

    //index
    int scanned_county_index = 0;
    //name
    char scanned_county_name[COUNTY_NAME_LENGTH] = {""};
    char scanned_counties_name[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH] = {""};
    //district
    int scanned_county_district = 0;
    //party
    char scanned_counties_party[4] = {""};
    //votes
    int scanned_county_votes = 0;
    int scanned_counties_votes[MAX_NUMBER_OF_COUNTIES][MAX_NUMBER_OF_PARTIES] = {0};

    //loop through file until end
    while (feof(file) == 0) {
        //Scan line
        fscanf(file, "%i \t %[^\t] \t %i \t %s \t %i\n",&scanned_county_index, &scanned_county_name, &scanned_county_district, &scanned_counties_party, &scanned_county_votes);

        //Count unique parties found so far
        int number_of_counties = count_counties(scanned_counties_name);

        //if scanned_party is not unique add the votes and continue the while loop
        if (is_party_in_counties(scanned_counties_name, scanned_county_name, number_of_counties)) {
            //find party index
            for (int i = 0; i < number_of_parties; i++) {
                if (strcmp(scanned_counties_party, parties_copy[i]) == 0) {
                    scanned_counties_votes[number_of_counties - 1][i] = scanned_county_votes;
                    break;
                }
            }
            continue;
        }

        //add scanned_party to list of unique parties
        strcpy(scanned_counties_name[number_of_counties], scanned_county_name);

        //copy into counties[i]
        counties[number_of_counties].index = scanned_county_index;
        strcpy(counties[number_of_counties].name, scanned_county_name);
        counties[number_of_counties].district = scanned_county_district;

        //copy votes into scanned_counties_votes[i]
        for (int i = 0; i < number_of_parties; i++) {
            if (strcmp(scanned_counties_party, parties_copy[i]) == 0) {
                scanned_counties_votes[number_of_counties][i] = scanned_county_votes;
                break;
            }
        }
    }
    //copy votes out of function, from scanned_counties_votes[i] into counties[i]
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) {
            counties[i].votes[j] = scanned_counties_votes[i][j];
        }
    }
}

int is_party_in_counties(char counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH], char to_find[], int string_length) {
    int result = 0;
    for (int i = 0; i < string_length; i++) {
        if (strcmp(counties[i], to_find) == 0) {
            result = 1;
            break;
        }
    }
    return result;
}

int count_counties(char counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH]) {
    int number_of_counties = 0;
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        if (strlen(counties[i]) == 0) continue;
        number_of_counties++;
    }
    return number_of_counties;
}