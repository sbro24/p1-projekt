#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "construct_state_header.h"
#include "header.h"


state_t construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {
    //TODO: Make state empty
    state_t state_results;

    //copy counties data
    county_t counties_copy[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        counties_copy[i].index = counties[i].index;
        strcpy(counties_copy[i].name, counties[i].name);
        counties_copy[i].district = counties[i].district;
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) counties_copy[i].votes[j] = counties[i].votes[j];
    }

    //int number_of_districts = count_districts(counties_copy);

    //get list of unique district number E.g {1, 2, 5 ,8}
    int district_numbers[MAX_NUMBER_OF_DISTRICTS] = {0};
    get_unique_district_numbers(district_numbers, counties);

    //copy parties for indexing
    char parties_copy[MAX_NUMBER_OF_PARTIES][4] = {""};
    for (int i = 0; i < number_of_parties; i++) strcpy(parties_copy[i], parties[i]);

    //sum all the votes in a district per party
    int district_votes[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES] = {0};
    sum_district_votes(district_votes, district_numbers, counties);
    //for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) printf("district_votes[%d] = { %d, %d, %d, %d, %d, %d }\n", i, district_votes[i][0], district_votes[i][1], district_votes[i][2], district_votes[i][3], district_votes[i][4], district_votes[i][5]);
    //add district_votes to state_t state_results
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        state_results.districts[i].district_number = district_numbers[i];
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) state_results.districts[i].votes[j] = district_votes[i][j];
    }

    //find party winner index of district and add it to state_results.number_of_seats
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        //returns the index of the winner of district i or returns -1 if district has not votes
        int winner = find_winner(state_results.districts[i].votes);
        if (winner == -1) continue;
        //+1 number_of_seats to the party that won
        state_results.number_of_seats[winner]++;
    }

    //sums up total votes per party to state_t state_results
    //loop over each party index i
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        //loop over all districts and sums to total_votes of party index i
        for (int j = 0; j < MAX_NUMBER_OF_DISTRICTS; j++) {
            state_results.total_votes[i] += state_results.districts[j].votes[i];
        }
    }

    return state_results;
}

int find_winner(int* votes) {
    //finds the biggest value in votes array
    int biggest = 0;
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        if (biggest < votes[i]) biggest = votes[i];
    }

    //finds the party with biggest votes
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        //if there are 0 votes in a district return -1 (no winners)
        if (biggest == 0) return -1;
        //return winner index
        if (votes[i] == biggest) return i;
    }
    //if all else fails return -1 (no winners)
    return -1;
}

void sum_district_votes(int district_votes[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES], int district_list[MAX_NUMBER_OF_DISTRICTS], county_t counties[MAX_NUMBER_OF_COUNTIES]) {
    //copy vote per county into 2d array of votes
    int county_votes[MAX_NUMBER_OF_COUNTIES][MAX_NUMBER_OF_PARTIES] = {0};
    //loop fer county
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        //loop per party in county[i]
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) county_votes[i][j] = counties[i].votes[j];
    }

    //iterate over each district
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        //iterate over each county and checks if it's district number i, and skips/continues if district number doesn't match
        for (int j = 0; j < MAX_NUMBER_OF_COUNTIES; j++) {
            if (district_list[i] != counties[j].district) continue;
            //if district number matches loop over each party in county j
            for (int k = 0; k < MAX_NUMBER_OF_PARTIES; k++) {
                //adds all the votes from county j to district i
                district_votes[i][k] += county_votes[j][k];
            }
        }
    }
}

void get_unique_district_numbers(int district_numbers[MAX_NUMBER_OF_DISTRICTS], county_t counties[MAX_NUMBER_OF_COUNTIES]) {
    int counter = 0;
    //copy all the counties district numbers
    int county_district_numbers[MAX_NUMBER_OF_COUNTIES] = {0};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) county_district_numbers[i] = counties[i].district;

    //TODO: only if district numbers lie beteen 1 - MAX_NUMBER_OF_DISTRICTS
    //iterate over unique districts found so far
    for (int i = 1; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        //find the first county with district number i
        for (int j = 0; j < MAX_NUMBER_OF_COUNTIES; j++) {
            if (county_district_numbers[j] == i) {
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