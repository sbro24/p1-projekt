#pragma once
#include <stdio.h>
#include "header.h"

FILE *open_file(const char *file_name, const char *mode);
int count_counties_in_struct(county_t counties[MAX_NUMBER_OF_COUNTIES]);

void construct_party_array(char parties[MAX_NUMBER_OF_PARTIES][4]);
void get_unique_parties(FILE* file, char parties[MAX_NUMBER_OF_PARTIES][4]);
int count_parties(char parties[MAX_NUMBER_OF_PARTIES][4]);
int is_string_in_array_of_strings(char parties[MAX_NUMBER_OF_PARTIES][4], char to_find[], int string_length);

void construct_county_array(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties);
void get_unique_counties(FILE* file, county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties);
int count_counties(char counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH]);
int is_party_in_counties(char counties[MAX_NUMBER_OF_COUNTIES][COUNTY_NAME_LENGTH], char to_find[], int string_length);

state_t construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties);
int count_districts(county_t counties[MAX_NUMBER_OF_COUNTIES]);
void get_unique_district_numbers(int district_numbers[MAX_NUMBER_OF_DISTRICTS], county_t counties[MAX_NUMBER_OF_COUNTIES]);
void sum_district_votes(int district_votes[MAX_NUMBER_OF_DISTRICTS][MAX_NUMBER_OF_PARTIES], int district_numbers[MAX_NUMBER_OF_DISTRICTS], county_t counties[MAX_NUMBER_OF_COUNTIES]);
int find_winner(int* votes);


int **CreateDistrictMap(int **countyMap, county_t counties[MAX_NUMBER_OF_COUNTIES], int county_number, int rows, int columns);
void GetDistrictGrid(int **districtMap, int **districtGrid, int districtID, int rows, int columns);