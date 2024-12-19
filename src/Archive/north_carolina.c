#include <stdbool.h>

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#define COUNTY_NAME_LENGTH 30

int count_counties(FILE *raw_file);

int main(void) {
    const char file_name[] = "us_house_north_carolina_results_2024.csv";

    char party[][4] = {
        "CST",
        "DEM",
        "GRE",
        "LIB",
        "REP",
        "UNA",
    };

    const int party_length = sizeof(party) / sizeof(party[0]);

    typedef struct {
        int index;
        char name[COUNTY_NAME_LENGTH];
        int district;
        int votes[party_length];
        int neighbors[10];
    } county_t;

    //Open file
    FILE *raw_file = fopen(file_name, "r");
    if (raw_file == NULL) {
        printf("Error opening file \"%s\"\n", file_name);
        exit(EXIT_FAILURE);
    }


    int number_of_counties = count_counties(raw_file);

    county_t counties[number_of_counties];



    //reset file pointer
    rewind(raw_file);
    //skip first line
    fscanf(raw_file, "%*[^\n]\n");

    char county_name[COUNTY_NAME_LENGTH];
    int county_district;
    int county_votes;
    char county_party[4];

    while (feof(raw_file) == false) {
        fscanf(raw_file, "%[^\t] \t %i \t %s \t %i\n", &county_name, &county_district, &county_party, &county_votes);

        printf("%s \t %i \t %s \t %i\n", county_name, county_district, county_party, county_votes);
        for (int i = 0; i < party_length; i++) {
            if (strcmp(county_party, party[i]) == 0) {

                //printf("%s\n", party[i]);
            }
        }
    }


    printf("The number of counties is: %d\n", number_of_counties);

    //printf("%s \t %i \t %s \t %i\n", first_line.county, first_line.district, first_line.party, first_line.votes);

    return 0;
}

int count_counties(FILE *raw_file) {
    //reset file pointer
    rewind(raw_file);
    //skip first line
    fscanf(raw_file, "%*[^\n]\n");

    int count = 0;
    char county_name[COUNTY_NAME_LENGTH], previous_county_name[COUNTY_NAME_LENGTH] = "";
    int county_district = 0, previous_county_district = 0;

    //loop through file until end
    while (feof(raw_file) == false) {
        //Scan line, county_name and county_district
        fscanf(raw_file, "%[^\t] \t %i \t %*s \t %*i\n", &county_name, &county_district);
        // if either county_name or county_district is different
        if (strcmp(county_name, previous_county_name) != 0 || county_district != previous_county_district) {
            //Count 1 up and insert county_name and county_district into previous_county_name and previous_county_district
            count++;
            strcpy(previous_county_name, county_name);
            previous_county_district = county_district;
        }
    }
    return count;
}



*/