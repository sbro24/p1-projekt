#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataimporter.h"
#include "construct_state_header.h"

void InitializeMatrixINT(int **matrix, int rows, int columns);
int **CreateDistrictMap(int **countyMap, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns);
void GetDistrictGrid(int **districtMap, int **districtGrid, int districtID, int rows, int columns);
void InitializeMatrixINT99(int **matrix, int rows, int columns);
void VoidCopy2dArrayINT(int **array1, int **array2, int rows, int columns);
void WriteAllDistrictMaps(state_t state, int rows, int columns);
void FreeAllDistrictMaps(state_t state, int rows);
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

  */

void dataimport_test(void) {
    printf("good 1\n");
    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    printf("good 2\n");
    construct_party_array(parties);
    printf("good 3\n");
    int number_of_parties = count_parties(parties);
    printf("good 4\n");
    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    printf("good 5\n");
    construct_county_array(counties, parties, number_of_parties);
    printf("good 6\n");
    state_t state = construct_state(counties, parties, number_of_parties);
    printf("good 7\n");


    int buf = 1000;
    FILE *file = open_file("grid_north_carolina_correctID_version2.csv", "r");
    //filesize f = ScanFile(file, buf);

    //char **dataStructSTR = Allocate2dCHARArray(f.lineCount, f.longestLine);
    //ReadFileDataInto2dCHARArray(file, dataStructSTR, f.lineCount, f.longestLine);

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

    WriteAllDistrictMaps(state, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);




    //Print2dArraySTR(dataStructSTR,f.lineCount);
    //Print2dArrayINT(dataStructINT,f.lineCount, f.longestLine);
    //Print2dArrayINT(districtMap,f.lineCount, f.longestLine);
    //Write2dArrayCHAR(dataStructSTR, f.lineCount, f.longestLine, "filetest1.txt", "w");
    //Write2dArrayINT(dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest1.txt", "w");
    //Write2dArrayINT(districtMap, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest2.txt", "w");
    //Write2dArrayINT(districtGrid, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest3.txt", "w");
    Write2dArrayINT(state.districts[1].grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest4.txt", "w");
    //Print2dArrayINT(districtGrid,f.lineCount, f.longestLine);



    //Free2dArrayCHAR(dataStructSTR,f.lineCount);
    FreeAllDistrictMaps(state, MAX_GRID_SIZE_Y);
    Free2dArrayINT(dataStructINT,MAX_GRID_SIZE_Y);
    Free2dArrayINT(districtMap,MAX_GRID_SIZE_Y);
    Free2dArrayINT(districtGrid,MAX_GRID_SIZE_Y);
    Free2dArrayINT(state.grid_map,MAX_GRID_SIZE_Y);
    //Free2dArrayINT(districtGrid,f.lineCount);


}


void InitializeMatrixINT(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
}

void InitializeMatrixINT99(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 99;
        }
    }
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

void VoidCopy2dArrayINT(int **array1, int **array2, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array2[i][j] = array1[i][j];
        }
    }
}

void WriteAllDistrictMaps(state_t state, int rows, int columns) {
    for (int i = 0; i < sizeof(state.districts); i++) {
        printf("good\n");
        int **districtMap = Allocate2dINTArray(rows, columns);
        GetDistrictGrid(state.grid_map, districtMap, state.districts[i].district_number, rows, columns);
        VoidAllocate2dINTArray(state.districts[i].grid_map, rows, columns);
        InitializeMatrixINT(state.districts[i].grid_map, rows, columns);
        VoidCopy2dArrayINT(districtMap, state.districts[i].grid_map, rows, columns);
        Free2dArrayINT(districtMap, rows);
    }
}

void FreeAllDistrictMaps(state_t state, int rows) {
    for (int i = 0; i < sizeof(state.districts); i++) {
        Free2dArrayINT(state.districts[i].grid_map, rows);
    }
}