#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "construct_state_header.h"
#include "header.h"


state_t construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {
    state_t state;

    county_t counties_copy[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        counties_copy[i].index = counties[i].index;
        strcpy(counties_copy[i].name, counties[i].name);
        counties_copy[i].district = counties[i].district;
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) counties_copy[i].votes[j] = counties[i].votes[j];
    }

    int number_of_districts = count_districts(counties_copy);

    int district_numbers[MAX_NUMBER_OF_DISTRICTS] = {0};
    get_district_numbers(district_numbers, counties);

    char parties_copy[MAX_NUMBER_OF_PARTIES][4] = {""};
    for (int i = 0; i < number_of_parties; i++) strcpy(parties_copy[i], parties[i]);

    int district_votes[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES] = {0};
    sum_district_votes(district_votes, district_numbers, counties);




    printf("Fucking construct_state AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");

    return state;
}

void sum_district_votes(int district_votes[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES], int district_list[MAX_NUMBER_OF_DISTRICTS], county_t counties[MAX_NUMBER_OF_COUNTIES]) {
    int district_list_copy[MAX_NUMBER_OF_DISTRICTS] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) district_list_copy[i] = district_list[i];

    int votes_copy[MAX_NUMBER_OF_COUNTIES][MAX_NUMBER_OF_PARTIES] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) votes_copy[i][j] = counties[i].votes[j];
    }

    int county_district_list_copy[MAX_NUMBER_OF_COUNTIES] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) county_district_list_copy[i] = counties[i].district;

    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        if (district_list_copy == 0) continue;
        for (int j = 0; j < MAX_NUMBER_OF_COUNTIES; j++) {
            if (district_list_copy[i] == county_district_list_copy[j]) {
                for (int k = 0; k < MAX_NUMBER_OF_PARTIES; k++) {
                    district_votes[i][k] += votes_copy[j][k];
                }
            }
        }
    }


    scanf("", &district_votes);






    /*
    int district_votes_copy[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES];

    int district_list_copy[MAX_NUMBER_OF_DISTRICTS] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) district_list_copy[i] = district_list[i];

    int votes[MAX_NUMBER_OF_COUNTIES][MAX_NUMBER_OF_PARTIES] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) votes[i][j] = counties[i].votes[j];
    }

    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_COUNTIES; j++) {
            if (district_list_copy[i] == counties[j].district) {
                for (int k = 0; k < MAX_NUMBER_OF_PARTIES; k++) *district_votes_copy[i] += votes[j][k];
            }
        }
    }
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) printf("district_votes_copy[%d] = %d\n", i, *district_votes_copy[i]);
    */
}

void get_district_numbers(int district_numbers[MAX_NUMBER_OF_DISTRICTS], county_t counties[MAX_NUMBER_OF_COUNTIES]) {
    int district_numbers_copy[MAX_NUMBER_OF_COUNTIES] = {0};
    int counter = 0;
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) district_numbers_copy[i] = counties[i].district;
    for (int i = 1; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_COUNTIES; j++) {
            if (district_numbers_copy[j] == i) {
                district_numbers[counter] = i;
                counter++;
                break;
            }
        }
    }
}

int count_districts(county_t counties[MAX_NUMBER_OF_COUNTIES]) {
    int count = 0;
    int county_districts[MAX_NUMBER_OF_COUNTIES] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) county_districts[i] = counties[i].district;
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        int check_int = county_districts[i];
        if (check_int == 0) continue;
        county_districts[i] = 0;
        count++;
        for (int j = i + 1; j < MAX_NUMBER_OF_COUNTIES; j++) {
            if (county_districts[j] == check_int) county_districts[j] = 0;
        }
    }
    return count;
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