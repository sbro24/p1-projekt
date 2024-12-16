
#ifndef EVAL_MAP_H
#define EVAL_MAP_H

#include "header.h"

typedef struct district_test_t {int id; int votes[2]; char name[30]; int map[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X];} district_test_t;

typedef struct {
    double x; // Row index
    double y; // Column index
} coordinate_t;

// write prototypes here
double eval_map(state_t state);

district_test_t *read_map_district(int no_of_districts, district_test_t districts[no_of_districts]);
district_test_t *create_district(int no_of_districts, district_test_t districts[no_of_districts]);
void read_map_to_district(int no_of_districts, district_test_t districts_test[no_of_districts]);

void print_district(int no_of_districts, district_test_t district_test[no_of_districts]);
coordinate_t* generate_coordinates(int rows, int cols, int** district, int district_no, int* count);
void print_results_to_txt(int district_no, int** district, double eval_fill, double eval_shape);

//hjælpefunktion
void calc_center (double* center_x, double* center_y, coordinate_t* coordinates, int count);
double calc_dist (coordinate_t* coordinate_point, double center_x, double center_y);

//funktioner til evaluering af udfyldning
double eval_fill(int count, coordinate_t coordinates[count]);
double calc_radius (int count);
double check_coordinate(int count, coordinate_t coordinates[count], double radius);

//funktioner til evaluering af formen
double eval_shape(int count, coordinate_t coordinates[count]);
double calc_avg_dist(int count, coordinate_t coordinates[count], double center_x, double center_y);

#endif //EVAL_MAP_H
