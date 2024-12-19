#include "header.h"
#include "construct_state_header.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <test.h>
#include <stdlib.h>

void construct_test_party_array(char parties[MAX_NUMBER_OF_PARTIES][4]) {

    //initialize test variables
    int total_amount_of_parties = 4;

    //Open the county file specified in "header.h"
    FILE* file = open_file("test_party_votes.csv", "r");

    //Declare an array of strings that's 4 characters long, E.g. {"D","E","M","\0"} (Party code + End char)
    char party_result[MAX_NUMBER_OF_PARTIES][4] = {""};

    get_unique_parties(file, party_result);

    //copy all the unique party codes into the string array parties specified in the function arguments
    for (int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) strcpy(parties[i], party_result[i]);

    for (int i = 0; i < 4; i++) {
        printf("%s\n", party_result[i]);
    }

    //Test if the correct amount of parties is counted
    if (count_parties(parties) == total_amount_of_parties) {
        printf("Number of parties = %d, test passed\n", count_parties(parties));
    }

    fclose(file);
}


void test_construct_county_array(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {

    //Initialize test variables
    int index_array[] = {1,2,3,4,5,6,7,8,9,10};
    int district_array[] = {9,5,5,8,5,11,3,1,7,7};
    int DEM_votes_array[] = {500,300,500,200,500,300,0,900,400,200};
    int REP_votes_array[] = {600,400,600,300,700,500,600,300,500,400};
    int UNA_votes_array[] = {700,0,0,0,0,0,0,0,0,0};
    int LIB_votes_array[] = {0,0,0,0,0,0,500,200,0,0};

    //Open the county file specified in "header.h"
    FILE* file = open_file("test_party_votes.csv", "r");

    //copy the list of parties in a new array
    char parties_copy[MAX_NUMBER_OF_PARTIES][4] = {""};
    for (int i = 0; i < number_of_parties; i++) strcpy(parties_copy[i], parties[i]);

    //declare the array of structs and make all the fields empty or 0
    county_t county_results[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};

    get_unique_counties(file, county_results, parties_copy, number_of_parties);

    //Declare a array of strings that's 4 characters long, E.g. {"D","E","M","\0"} (Party code + End char)
    char party_result[MAX_NUMBER_OF_PARTIES][4] = {""};

    get_unique_parties(file, party_result);

    //copy all the results into county_t counties specified in the function arguments
    //and print to test if data is correct
    for (int i = 0; i < 10; i++) {
        counties[i].index = county_results[i].index;
        printf("%d, ", counties[i].index);
        strcpy(counties[i].name, county_results[i].name);
        printf("%s, ", counties[i].name);
        counties[i].district = county_results[i].district;
        printf("%d, ", counties[i].district);
        for (int j = 0; j < 4; j++) {
            counties[i].votes[j] = county_results[i].votes[j];
            printf("%s %d, ", party_result[j], counties[i].votes[j]);
        }
        printf("\n");
    }

    //Test if index and district numbers are read correctly
    //Test needs to run 10 times to pass
    for (int i = 0; i < 10; i++) {
        if (counties[i].index == index_array[i] && counties[i].district == district_array[i])
            printf("correct index and district test %d passed\n", i+1);
    }

    //Test if votes for each party per index are read correctly
    //This test needs to run 10 times to pass
    for (int i = 0; i < 10; i++) {
        int j = 0;
            if (counties[i].votes[j] == DEM_votes_array[i]
                && counties[i].votes[j+1] == REP_votes_array[i]
                && counties[i].votes[j+2] == UNA_votes_array[i]
                && counties[i].votes[j+3] == LIB_votes_array[i])
                printf("correct votes test %d passed\n", i+1);
    }

    fclose(file);
}

state_t test_construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties) {

    //initialize total amount of votes for each party
    int DEM_total_votes = 3800;
    int REP_total_votes = 4900;
    int UNA_total_votes = 700;
    int LIB_total_votes = 700;
    int total_votes_array[] = {DEM_total_votes, REP_total_votes,
        UNA_total_votes, LIB_total_votes};

    //initialize district1 test variables
    int DEM_votes_district1 = 900;
    int REP_votes_district1 = 300;
    int UNA_votes_district1 = 0;
    int LIB_votes_district1 = 200;
    int votes_district1_array[] = {DEM_votes_district1, REP_votes_district1,
        UNA_votes_district1, LIB_votes_district1};

    //initialize total amount of seats for each party
    int DEM_total_seats = 1;
    int REP_total_seats = 5;
    int UNA_total_seats = 1;
    int LIB_total_seats = 0;
    int total_seats_array[] = {DEM_total_seats, REP_total_seats,
        UNA_total_seats, LIB_total_seats};


    state_t state_results = {{0, {0}, {{0}}},{0}, {0},{0}};

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
    for (int i = 0; i < 4; i++) {
        //loop over all districts and sums to total_votes of party index i
        for (int j = 0; j < 7; j++) {
            state_results.total_votes[i] += state_results.districts[j].votes[i];
            printf("%d %d\n", state_results.districts[j].district_number, state_results.districts[j].votes[i]);
        }
    }

    //Test if the correct number of votes for each party for the first district is counted
    for (int i = 0; i < 4; i++) {
        if (state_results.districts[0].district_number == 1 && state_results.districts[0].votes[i] == votes_district1_array[i]) {
            printf("district 1 party votes test %d passed\n", i+1);
        }
    }

    //Test if number of seats and total votes per party are read and counted correctly
    //This test needs to complete 4 times to pass
    for (int i = 0; i < 4; i++) {
        if (state_results.number_of_seats[i] == total_seats_array[i] && state_results.total_votes[i] == total_votes_array[i]) {
            printf("number of seats and total votes test %d passed\n", i);
        }
    }

        return state_results;
}

