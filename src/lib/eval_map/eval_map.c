#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eval_map.h>
#include <string.h>

#include "dataimporter.h"
#include "header.h"

/**
 * An evaluation of the state map in terms of fill and distance to center
 * @param no_of_districts the total number of districts in state
 * @param districts array of district structs containing grid-maps
 * @return  an index between 0 and 100
 */
double eval_map(state_t state) {
    coordinate_t* coordinates = NULL; //initialization of array of structs containing coordinates.
    int count = 0;

    Print2dArrayINT(state.grid_map, MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X);

    double  evaluation_fill = 0,
            evaluation_fill_akk = 0,
            evaluation_shape = 0,
            evaluation_shape_akk = 0,
            evaluation_map = 0,
            evaluation_map_akk = 0;


    for (int i = 1; i <= 14; i++) {

        coordinates = generate_coordinates(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, state.grid_map, i, &count);

        evaluation_fill = eval_fill(count, coordinates);
        printf("Evaluation of fil: %lf\n", evaluation_fill);
        evaluation_fill_akk += evaluation_fill;

        evaluation_shape = eval_shape(count, coordinates);
        printf("Evaluation of shape: %lf\n", evaluation_shape);
        evaluation_shape_akk += evaluation_shape;

        evaluation_map = (evaluation_fill + evaluation_shape)/2;
        printf("Evaluation of map: %lf\n", evaluation_map);
        evaluation_map_akk += evaluation_map;

        free(coordinates);

    }


    /*
    int district = 15;
    char file_name_path[30] = {"src/Output_files/output_district_"};
    char file_name[30];
    snprintf(file_name, sizeof(file_name), "%s%d.txt", file_name_path, district);

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "__________________\n");
    fprintf(file, "eval_fill: %lf\n", evaluation_fill);
    fprintf(file, "eval_shape: %lf\n", evaluation_shape);
    fprintf(file, "eval_map: %lf\n", evaluation_map);

    // Print the 2D array to the file
    fprintf(file, "2D Array:\n");
    for (int i = 0; i < MAX_GRID_SIZE_Y; i++) {
        for (int j = 0; j < MAX_GRID_SIZE_X; j++) {
            fprintf(file, " %d ", state.grid_map[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X]);
        }
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);
*/
    return evaluation_map;
}

/**
 *
 * @param rows number of rows in the grid-map of the state
 * @param cols number of columns in the grid-map of state
 * @param district grid-map of a district
 * @param count number of grids in the district
 * @return an array of (x, y) coordinates
 */

coordinate_t* generate_coordinates(int rows, int cols, int** district, int district_no, int* count) {

    *count = 0; // Initialize count

    // Allocate memory for the coordinates (worst case: every element has a coordinate)
    coordinate_t* coordinates = malloc(rows * cols * sizeof(coordinate_t));

    // Traverse the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (district[i][j] == district_no) { // Only add coordinates for non-zero elements
                coordinates[*count].y = i+0.5;
                coordinates[*count].x = j+0.5;
                (*count)++;
            }
        }
    }

    return coordinates;
}

/**
 * Calculates a weighted center of the district
 * @param center_x center of the district
 * @param center_y center of the district
 * @param coordinates array of coordinates generated from grid-map
 * @param count number of coordinates
 */
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

/**
 * Calculates the size of the smallest possible circle containing the number of coordinates in the district
 * @param count number of coordinates in district
 * @return radius of optimal cirkle
 */
double calc_radius (int count) {
    return sqrt(count / (M_PI));
}

/*
   int district = 15;
   char file_name_path[30] = {"src/Output_files/output_district_"};
   char file_name[30];
   snprintf(file_name, sizeof(file_name), "%s%d.txt", file_name_path, district);


   FILE *file = fopen(file_name, "w");
   if (file == NULL) {
       perror("Error opening file");
       return 1;
   }

   fprintf(file, "__________________\n");
   fprintf(file, "eval_fill: %lf\n", evaluation_fill);
   fprintf(file, "eval_shape: %lf\n", evaluation_shape);
   fprintf(file, "eval_map: %lf\n", evaluation_map);

   // Print the 2D array to the file
   fprintf(file, "2D Array:\n");
   for (int i = 0; i < MAX_GRID_SIZE_Y; i++) {
       for (int j = 0; j < MAX_GRID_SIZE_X; j++) {
           fprintf(file, " %d ", districts_test[1].map[i][j]);
       }
       fprintf(file, "\n");
   }

   // Close the file
   fclose(file);

   */