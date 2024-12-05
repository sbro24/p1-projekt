#pragma once
#include <stdio.h>
#include "header.h"

void construct_counties(void);
FILE *open_file(const char *file_name, const char *mode);
void construct_party_array(char parties[MAX_NUMBER_OF_PARTIES][4]);
void get_unique_parties(FILE* file, char parties[MAX_NUMBER_OF_PARTIES][4]);
int is_string_in_array(char string[MAX_NUMBER_OF_PARTIES][4], char to_find[], int string_length);
int count_parties();