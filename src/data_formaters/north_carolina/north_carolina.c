#include <stdbool.h>

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNTY_NAME_LENGTH 30

void copy_array(char from[], char to[]);
int compare_strings(const char *a, const char *b, int length);

int main(void) {
    char party[][3] = {
        "CST",
        "DEM",
        "GRE",
        "LIB",
        "REP",
        "UNA",
    };

    const int party_length = sizeof(party) / sizeof(party[0]);

    struct county_t {
        char name[COUNTY_NAME_LENGTH];
        int district;
        int votes[party_length];
    };
    typedef struct county_t county_t;

    //Open file
    FILE *raw_file = fopen("us_house_north_carolina_results_2024.csv", "r");
    if (raw_file == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    //skip first line
    fscanf(raw_file, "%*[^\n]\n");

    //count the number of unique counties
    int number_of_counties = 0;
    //check if county name n - 1 is different for county name n
    char county_name[COUNTY_NAME_LENGTH];
    char previous_county_name[COUNTY_NAME_LENGTH] = "AAAAAAAAAAAA";
    int county_district = 0;
    int previous_county_district = 0;

    //loop through file
    while (feof(raw_file) == false) {
        fscanf(raw_file, "%[^\t] \t %i \t %*s \t %*i\n", &county_name, &county_district);
        // if (county_name == previous_county_name) number_of_counties++
        if (strcmp(county_name, previous_county_name) != 0 || county_district != previous_county_district) {
            printf("%s %i != %s %i\n", county_name, county_district, previous_county_name, previous_county_district);
            number_of_counties++;
            strcpy(previous_county_name, county_name);
            previous_county_district = county_district;
        }
    }

    //reset file pointer
    rewind(raw_file);

    printf("The number of counties is: %d\n", number_of_counties);

    //printf("%s \t %i \t %s \t %i\n", first_line.county, first_line.district, first_line.party, first_line.votes);

    return 0;
}

