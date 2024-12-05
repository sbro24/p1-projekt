#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <string.h>


void construct_county_array(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {
    printf("Fucking construct_county_array AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");

    FILE* file = open_file(FILE_COUNTIES, "r");

    //name
    char county_name_result[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH] = {""};
    get_unique_counties(file, county_name_result);

    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        strcpy(counties[i].name, county_name_result[i]);
        printf("%s\n", counties[i].name);
    }

    fclose(file);
}

void get_unique_counties(FILE* file, char counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH]) {
    //reset file pointer
    rewind(file);
    //skip first line
    fscanf(file, "%*[^\n]\n");

    char scanned_county[COUNTY_NAME_LENGTH];
    char scanned_counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH] = {""};

    //loop through file until end
    while (feof(file) == 0) {
        //Scan line, for Party
        fscanf(file, "%*i \t %[^\t] \t %*i \t %*s \t %*i\n", &scanned_county);

        //Count unique parties found so far
        int number_of_counties = count_counties(scanned_counties);

        //continue if scanned_party is not unique
        if (is_party_in_counties(scanned_counties, scanned_county, number_of_counties)) continue;

        strcat(scanned_counties[number_of_counties], scanned_county);

    }
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) strcat(counties[i], scanned_counties[i]);
}

int is_party_in_counties(char counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH], char to_find[], int string_length) {
    int result = 0;

    for (int i = 0; i < string_length; i++) {
        if (!strcmp(counties[i], to_find)) {
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