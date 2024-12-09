#pragma once

#define INPUT_DIRECTORY "input_files"
#define FILE_COUNTIES "us_house_north_carolina_results_2024_index.txt"
#define FILE_GRID "path.csv"
#define FILE_GRAPH "path.csv"
#define FILE_POPULATION "path.csv"

#define MAX_NUMBER_OF_PARTIES 10
#define MAX_NUMBER_OF_DISTRICTS 20
#define MAX_NUMBER_OF_COUNTIES 150
#define MAX_NUMBER_OF_NEIGHBORS 10

#define MAX_GRID_SIZE_X 200
#define MAX_GRID_SIZE_Y 100

#define COUNTY_NAME_LENGTH 30

//district struct
typedef struct {
    int district_number;
    int votes[MAX_NUMBER_OF_PARTIES];
    int grid_map[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X];
} district_t;

//state struct
typedef struct {
    district_t districts[MAX_NUMBER_OF_DISTRICTS];
    int number_of_seats[MAX_NUMBER_OF_PARTIES];
    int total_votes[MAX_NUMBER_OF_PARTIES];
    int grid_map[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X];
} state_t;

typedef struct {
    int index;
    char name[COUNTY_NAME_LENGTH];
    int district;
    int votes[MAX_NUMBER_OF_PARTIES];
    int neighbors[MAX_NUMBER_OF_NEIGHBORS];
} county_t;

state_t construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties);
void error_handling(char *message);
