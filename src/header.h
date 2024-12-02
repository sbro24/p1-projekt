#pragma once

#define FILE_COUNTIES "path.csv"
#define FILE_GRID "path.csv"
#define FILE_GRAPH "path.csv"
#define FILE_POPULATION "path.csv"

#define MAX_NUMBER_OF_PARTIES 10
#define MAX_NUMBER_OF_DISTRICTS 20
#define MAX_NUMBER_OF_COUNTIES 200
#define MAX_NUMBER_OF_NEIGHBORS 10

#define MAX_GRID_SIZE_X 300
#define MAX_GRID_SIZE_Y 150

#define COUNTY_NAME_LENGTH 30

//district struct
typedef struct {
    int district_number;
    int votes[MAX_NUMBER_OF_PARTIES];
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
    int neighbors[10];
} county_t;

state_t construct_state(void);