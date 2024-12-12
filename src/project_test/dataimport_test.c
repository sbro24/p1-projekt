#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataimporter.h"
#include "construct_state_header.h"

void InitializeMatrixINT(int **matrix, int rows, int columns);
int **CreateDistrictMap(int **countyMap, int districts, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns);
int **GetDistrictGrid(int **districtMap, int districtID, int rows, int columns);


void dataimport_test(void) {
    int buf = 500;
    FILE *file = open_file("grid_north_carolina.csv", "r");
    filesize f = ScanFile(file, buf);
    char **dataStructSTR = Allocate2dCHARArray(f.lineCount, f.longestLine);
    ReadFileDataInto2dCHARArray(file, dataStructSTR, f.lineCount, f.longestLine);
    fclose(file);
    int **dataStructINT = ConvertToInt(dataStructSTR, f.lineCount, f.longestLine);

    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_party_array(parties);
    int number_of_parties = count_parties(parties);
    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    construct_county_array(counties, parties, number_of_parties);


    int **districtMap = CreateDistrictMap(dataStructINT, 14, counties, count_counties_in_struct(counties), f.lineCount, f.longestLine);
    int **districtGrid = GetDistrictGrid(districtMap, counties[1].district, f.lineCount, f.longestLine);

    //Print2dArraySTR(dataStructSTR,f.lineCount);
    //Print2dArrayINT(dataStructINT,f.lineCount, f.longestLine);
    Print2dArrayINT(districtMap,f.lineCount, f.longestLine);
    //Print2dArrayINT(districtGrid,f.lineCount, f.longestLine);

    Free2dArrayCHAR(dataStructSTR,f.lineCount);
    Free2dArrayINT(dataStructINT,f.lineCount);
    Free2dArrayINT(districtMap,f.lineCount);
    Free2dArrayINT(districtGrid,f.lineCount);

}


void InitializeMatrixINT(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
}

int **CreateDistrictMap(int **countyMap, int districts, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns) {
    int **districtMap = Allocate2dINTArray(rows, columns);
    InitializeMatrixINT(districtMap, rows, columns);
    for (int i = 1; i <= districts; i++) {
        for (int j = 0; j <= county_number; j++) {
            if (counties[j].district != 0) {
                for (int k = 0; k < rows; k++) {
                    for (int l = 0; l < columns; l++) {
                        if (countyMap[k][l] == j && districtMap[k][l] == 0) {
                            districtMap[k][l] = counties[j].district;
                        }
                    }
                }
            }
        }
    }
    return districtMap;
}

int **GetDistrictGrid(int **districtMap, int districtID, int rows, int columns) {
    int **districtGrid = Allocate2dINTArray(rows, columns);
    InitializeMatrixINT(districtMap, rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(districtMap[i][j] == districtID) {
                districtMap[i][j] = 1;
            }
        }
    }
    return districtGrid;
}