
#ifndef EVAL_MAP_H
#define EVAL_MAP_H

#include "header.h"

typedef struct {
    double x; // Row index
    double y; // Column index
} coordinate_t;

double eval_map(state_t state);
coordinate_t* generate_coordinates(int rows, int cols, int** district, int district_no, int* count);
void print_results_to_txt(int district_no, int** district, double eval_fill, double eval_shape);

//functions in evaluate fill
double eval_fill(int count, coordinate_t coordinates[count]);
double calc_radius (int count);
double check_coordinate(int count, coordinate_t coordinates[count], double radius);

//functions in evaluate shape
double eval_shape(int count, coordinate_t coordinates[count]);
double calc_avg_dist(int count, coordinate_t coordinates[count], double center_x, double center_y);

//functions use in both evaluate shape and evaluate fill
void calc_center (double* center_x, double* center_y, coordinate_t* coordinates, int count);
double calc_dist (coordinate_t* coordinate_point, double center_x, double center_y);

#endif //EVAL_MAP_H
