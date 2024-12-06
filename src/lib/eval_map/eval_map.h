
#ifndef EVAL_MAP_H
#define EVAL_MAP_H

typedef struct {
    double x; // Row index
    double y; // Column index
} coordinate;

// write prototypes here
void read_district (int district[10][10]);
void print_district (int district[10][10]);
coordinate* generate_coordinates(int rows, int cols, int district[rows][cols], int* count);

//hjælpefunktion
void calc_center (double* center_x, double* center_y, coordinate* coordinates, int count);
double calc_dist (coordinate* coordinate_point, double center_x, double center_y);

//funktioner til evaluering af udfyldning
double eval_fill(int count, coordinate coordinates[count]);
double calc_radius (int count);
double check_coordinate(int count, coordinate coordinates[count], double radius);

//funktioner til evaluering af formen
double eval_shape(int count, coordinate coordinates[count]);
double calc_avg_dist(int count, coordinate coordinates[count], double center_x, double center_y);

#endif //EVAL_MAP_H
