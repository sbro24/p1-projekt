#pragma once

#define MAX_NUMBER_OF_PARTIES 10
#define MAX_NUMBER_OF_DISTRICTS 20
#define MAX_NUMBER_OF_COUNTIES 200

#define MAX_GRID_SIZE_X 300
#define MAX_GRID_SIZE_Y 150


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

void construct_state(void);