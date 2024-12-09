#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eval_map.h>
#include "header.h"

double eval_map(int no_of_districts, district_t districts[no_of_districts]) {

    district_t district_copy[MAX_NUMBER_OF_DISTRICTS];
    for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
        district_copy[i] = districts[i];
    }


    coordinate_t* coordinates = NULL;

    double  evaluation_fill = 0,
            evaluation_fill_akk = 0,
            evaluation_shape = 0,
            evaluation_shape_akk = 0,
            evaluation_map = 0,
            evaluation_map_akk = 0;

    for (int i = 0; i < no_of_districts; i++) {
        int count = 0; // To store the number of coordinates generated
        //coordinates = generate_coordinates(MAX_GRID_SIZE_X, MAX_GRID_SIZE_Y, districts[i].grid_map, &count);
        if (count == 0) {
            continue;
        } else {
            evaluation_fill = eval_fill(count, coordinates);
            evaluation_fill_akk += evaluation_fill;

            evaluation_shape = eval_shape(count, coordinates);
            evaluation_shape_akk += evaluation_shape;

            evaluation_map = (evaluation_fill + evaluation_shape)/2;
            evaluation_map_akk += evaluation_map;

            if (coordinates) {
                free(coordinates);
                coordinates = NULL;
            }
        }
    }

    return evaluation_map;
}

coordinate_t* generate_coordinates(int rows, int cols, int district[rows][cols], int* count) {
    *count = 0; // Initialize count

    // Allocate memory for the coordinates (worst case: every element has a coordinate)
    coordinate_t* coordinates = malloc(rows * cols * sizeof(coordinate_t));

    // Traverse the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (district[i][j] != 0) { // Only add coordinates for non-zero elements
                coordinates[*count].x = i+0.5;
                coordinates[*count].y = j+0.5;
                (*count)++;
            }
        }
    }

    return coordinates;
}

void print_district (int district[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y]) {

    printf("Map: \n");
    printf("___________________________________\n");
    for (int i = 0; i<MAX_GRID_SIZE_X; i++) {
        for(int j = 0; j<MAX_GRID_SIZE_Y; j++) {
            if (district[i][j] == 1 ) {
                printf(" %d ", district[i][j]);
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
    printf("___________________________________\n");
}

void calc_center (double* center_x, double* center_y, coordinate_t* coordinates, int count) {
    double sum_of_x = 0;
    double sum_of_y = 0;

    for (int i = 0; i < count; i++) {
        sum_of_x += coordinates[i].x;
        sum_of_y += coordinates[i].y;
    }

    *center_x = (double) sum_of_x/count;
    *center_y = (double) sum_of_y/count;

}

double calc_radius (int count) {
    return sqrt(count / (M_PI));
}
