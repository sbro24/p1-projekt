#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataimporter.h"
#include "construct_state_header.h"

void InitializeMatrixINT(int **matrix, int rows, int columns);
int **CreateDistrictMap(int **countyMap, int districts, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns);
void GetDistrictGrid(int **districtMap, int **districtGrid, int districtID, int rows, int columns);
void InitializeMatrixINT99(int **matrix, int rows, int columns);
// MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X
// f.lineCount, f.longestLine

void dataimport_test(void) {
    int buf = 1000;
    FILE *file = open_file("grid_north_carolina_correctID_version2.csv", "r");
    filesize f = ScanFile(file, buf);

    //char **dataStructSTR = Allocate2dCHARArray(f.lineCount, f.longestLine);
    //ReadFileDataInto2dCHARArray(file, dataStructSTR, f.lineCount, f.longestLine);

    int **dataStructINT = Allocate2dINTArray(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    ReadFileDataInto2dINTArray(file, dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, ";");
    fclose(file);


    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_party_array(parties);
    int number_of_parties = count_parties(parties);
    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    construct_county_array(counties, parties, number_of_parties);


    int **districtMap = CreateDistrictMap(dataStructINT, 14, counties, count_counties_in_struct(counties), MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    int **districtGrid = Allocate2dINTArray(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    InitializeMatrixINT(districtGrid, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);
    GetDistrictGrid(districtMap, districtGrid, counties[1].district, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);

    //Print2dArraySTR(dataStructSTR,f.lineCount);
    //Print2dArrayINT(dataStructINT,f.lineCount, f.longestLine);
    //Print2dArrayINT(districtMap,f.lineCount, f.longestLine);
    //Write2dArrayCHAR(dataStructSTR, f.lineCount, f.longestLine, "filetest1.txt", "w");
    Write2dArrayINT(dataStructINT, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest1.txt", "w");
    Write2dArrayINT(districtMap, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest2.txt", "w");
    Write2dArrayINT(districtGrid, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, "filetest3.txt", "w");
    //Print2dArrayINT(districtGrid,f.lineCount, f.longestLine);

    //Free2dArrayCHAR(dataStructSTR,f.lineCount);
    Free2dArrayINT(dataStructINT,MAX_GRID_SIZE_Y);
    Free2dArrayINT(districtMap,MAX_GRID_SIZE_Y);
    Free2dArrayINT(districtGrid,MAX_GRID_SIZE_Y);
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

int **CreateDistrictMap(int **countyMap, int districts, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns) {
    int **districtMap = Allocate2dINTArray(rows, columns);
    InitializeMatrixINT(districtMap, rows, columns);
        for (int j = 0; j < county_number; j++) {
            if (counties[j].district != 0) {
                for (int k = 0; k < rows; k++) {
                    for (int l = 0; l < columns; l++) {
                        if (countyMap[k][l] == counties[j].index && districtMap[k][l] == 0) {
                            //printf("current county = %d, district = %d\n", counties[j].index, counties[j].district);
                            districtMap[k][l] = counties[j].district;
                            //printf("result = %d\n", districtMap[k][l]);
                        }
                    }
                }
            }
            else {
                //printf("district not found\n");
                //printf("current county = %d, district = %d\n", j, counties[j].district);

            }

    }
    return districtMap;
}

void GetDistrictGrid(int **districtMap, int **districtGrid, int districtID, int rows, int columns) {
    printf("district ID %d\n", districtID);
    for (int i = 0; i < rows; i++) {
        //printf("i = %d\n", i);
        for (int j = 0; j < columns; j++) {
            //printf("j = %d\n", j);
            if(districtMap[i][j] == districtID) {

                //printf("j = %d\n", j);
                districtGrid[i][j] = 1;
            }
        }
    }
}