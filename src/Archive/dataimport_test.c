#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataimporter.h"
#include "construct_state_header.h"


// MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X
// f.lineCount, f.longestLine

 /*
state struct
typedef struct {
    district_t districts[MAX_NUMBER_OF_DISTRICTS];
    int number_of_seats[MAX_NUMBER_OF_PARTIES];
    int total_votes[MAX_NUMBER_OF_PARTIES];
    int grid_map[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X];
} state_t;

typedef struct {
   int district_number;
   int votes[MAX_NUMBER_OF_PARTIES];
   int grid_map[100][70]; //works
   //int grid_map[MAX_GRID_SIZE_X][59]; //doesn't work
   //int grid_map[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X];
} district_t;

typedef struct {
    int index;
    char name[COUNTY_NAME_LENGTH];
    int district;
    int votes[MAX_NUMBER_OF_PARTIES];
    int neighbors[MAX_NUMBER_OF_NEIGHBORS];
} county_t;



void dataimport_test(void) {
    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_party_array(parties);
    int number_of_parties = count_parties(parties);
    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    construct_county_array(counties, parties, number_of_parties);
    state_t state = construct_state(counties, parties, number_of_parties);


    FILE *file = open_file("grid_north_carolina_correctID_version2.csv", "r");
    int **dataStructINT = Allocate2dINTArray(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    ReadFileDataInto2dINTArray(file, dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, ";");
    fclose(file);

    int **districtMap = CreateDistrictMap(dataStructINT, counties, count_counties_in_struct(counties), MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    int **districtGrid = Allocate2dINTArray(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(districtGrid, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    GetDistrictGrid(districtMap, districtGrid, counties[1].district, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);

    // write state-wide district map to state.grid_map
    VoidAllocate2dINTArray(state.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(state.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    VoidCopy2dArrayINT(districtMap, state.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);





    //Print2dArraySTR(dataStructSTR,f.lineCount);
    //Print2dArrayINT(dataStructINT,f.lineCount, f.longestLine);
    //Print2dArrayINT(districtMap,f.lineCount, f.longestLine);
    //Write2dArrayCHAR(dataStructSTR, f.lineCount, f.longestLine, "filetest1.txt", "w");
    //Write2dArrayINT(dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest1.txt", "w");
    //Write2dArrayINT(districtMap, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest2.txt", "w");
    //Write2dArrayINT(districtGrid, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest3.txt", "w");
    //Write2dArrayINT(state.districts[1].grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest4.txt", "w");
    //Print2dArrayINT(districtGrid,f.lineCount, f.longestLine);



    //Free2dArrayCHAR(dataStructSTR,f.lineCount);
    Free2dArrayINT(dataStructINT,MAX_GRID_SIZE_Y);
    Free2dArrayINT(districtMap,MAX_GRID_SIZE_Y);
    Free2dArrayINT(districtGrid,MAX_GRID_SIZE_Y);
    Free2dArrayINT(state.grid_map,MAX_GRID_SIZE_Y);
    //Free2dArrayINT(districtGrid,f.lineCount);


}

*/