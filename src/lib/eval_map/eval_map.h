
#ifndef EVAL_MAP_H
#define EVAL_MAP_H

#include "header.h"

typedef struct {
    double x; // Row index
    double y; // Column index
} coordinate_t;

// write prototypes here
double eval_map(int no_of_districts, district_t districts[no_of_districts]);

void print_district(int district[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y]);
coordinate_t* generate_coordinates(int rows, int cols, int district[rows][cols], int* count);

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
