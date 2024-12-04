#pragma once
#include <stdio.h>

void construct_counties(void);
FILE *open_file(const char *file_name, const char *mode);
int calc_number_of_parties(FILE* file);