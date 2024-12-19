#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/DataImporter/dataimporter.h"
#include "../lib/construct_state/construct_state_header.h"
#include "../project_test/test.h"
#include "../header.h"
#include "../lib/output/output.h"
#include "../lib/eval_map/eval_map.h"

void dataimport_test_output(void) {
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

    printf("Function start\n");
    int **gridArray = Allocate2dINTArray(f.lineCount, f.longestLine);

    for (int m = 0; m < f.lineCount; m++) {
        for (int n = 0; n < f.longestLine; n++) {
            gridArray[m][n] = 0;
        }
    }
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < count_counties_in_struct(counties); j++) {
            for (int k = 0; k < f.lineCount; k++) {
                for (int l = 0; l < f.longestLine; l++) {
                    if (dataStructINT[k][l] == counties[i].district && gridArray[k][l] == 0) {
                        gridArray[k][l] = i;
                    }
                }
            }
        }
    }








    Print2dArrayINT(gridArray,f.lineCount, f.longestLine);

    Free2dArrayCHAR(dataStructSTR,f.lineCount);
    Free2dArrayINT(dataStructINT,f.lineCount);
    Free2dArrayINT(gridArray,f.lineCount);

}


/*
void output_to_txt(const char *test_output)
{
    // open the file for writing
    FILE *fp = freopen("Output_files/output_to_txt.txt",
        "w", stdout);
    if (fp == NULL)
    {
        printf("Error opening the file %s", test_output);
        EXIT_FAILURE;
    }

    dataimport_test_output();

    // close the file
    fclose(fp);
}
*/
void output_to_txt2(void (*f)(void))
{
    // open the file for writing
    FILE *fp = freopen("Output_files/output_to_txt.txt",
        "w", stdout);
    if (fp == NULL)
    {
        printf("Error opening the file %p", &fp);
        EXIT_FAILURE;
    }

    f();

    // close the file
    fclose(fp);
}