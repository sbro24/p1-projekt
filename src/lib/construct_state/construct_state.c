#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataimporter.h"
#include "construct_state_header.h"
#include "header.h"

/**
* collects and calculates all the data needed in to a struct
* @param county_t array with all the counties
* @param array with all the unique parties codes
* @param int of how many unique parties codes there are
* @return state_t with all the data eval needs
*/
state_t construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {
    state_t state_results = {{0, {0}, {{0}}},{0}, {0},{0}};

    //copy counties data
    county_t counties_copy[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    for (int i = 0; i < MAX_NUMBER_OF_COUNTIES; i++) {
        counties_copy[i].index = counties[i].index;
        strcpy(counties_copy[i].name, counties[i].name);
        counties_copy[i].district = counties[i].district;
        for (int j = 0; j < MAX_NUMBER_OF_PARTIES; j++) counties_copy[i].votes[j] = counties[i].votes[j];
    }

    //get list of unique district number E.g {1, 2, 5 ,8}
    int district_numbers[MAX_NUMBER_OF_DISTRICTS] = {0};
    get_unique_district_numbers(district_numbers, counties);

    //copy parties for indexing
    char parties_copy[MAX_NUMBER_OF_PARTIES][4] = {""};
    for (int i = 0; i < number_of_parties; i++) strcpy(parties_copy[i], parties[i]);

    //sum all the votes in a district per party
    int district_votes[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES] = {0};
    sum_district_votes(district_votes, district_numbers, counties);
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

    FILE *file = open_file("grid_north_carolina_correctID_version2.csv", "r");
    int **dataStructINT = Allocate2dINTArray(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    ReadFileDataInto2dINTArray(file, dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, ";");
    fclose(file);


    // write state-wide district map to state.grid_map
    int **districtMap = CreateDistrictMap(dataStructINT, counties, count_counties_in_struct(counties), MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    VoidAllocate2dINTArray(state_results.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(state_results.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    VoidCopy2dArrayINT(districtMap, state_results.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);

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

int **CreateDistrictMap(int **countyMap, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns) {
    int **districtMap = Allocate2dINTArray(rows, columns);
    InitializeMatrixINT(districtMap, rows, columns);
    for (int j = 0; j < county_number; j++) {
        if (counties[j].district != 0) {
            for (int k = 0; k < rows; k++) {
                for (int l = 0; l < columns; l++) {
                    if (countyMap[k][l] == counties[j].index && districtMap[k][l] == 0) {
                        districtMap[k][l] = counties[j].district;
                    }
                }
            }
        }
        else {
            printf("district not found\n");

        }

    }
    return districtMap;
}

void GetDistrictGrid(int **districtMap, int **districtGrid, int districtID, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(districtMap[i][j] == districtID) {
                districtGrid[i][j] = 1;
            }
        }
    }
}