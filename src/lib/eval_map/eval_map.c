#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eval_map.h>
#include "header.h"

/**
 * An evaluation of the state map in terms of fill and distance to center
 * @param state node from a state-struct containing a gridmap of the districts
 * @return  an index between 0 and 100
 */
double eval_map(state_t state) {

    coordinate_t* coordinates = {0}; //initialises an array of structs containing coordinates.
    int count_coordinates = 0; //counts the number of coordinates in a district
    int count_districts = 0; //counts the number of districts in the state

    //Initialization of relevant variables for evaluation of map
    double  evaluation_fill_district = 0,
            evaluation_shape_district = 0,
            evaluation_map_district = 0,
            evaluation_map_akk = 0;


    //evaluates each district map separately and sums up the scores
    for (int i = 1; i <= 14; i++) {
        if (state.districts[i-1].district_number != 0) {

            //generates coordinates for the district
            coordinates = generate_coordinates(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, state.grid_map, i, &count_coordinates);

            //evaluates parameters and akkumulates evaluation parameters
            evaluation_fill_district = eval_fill(count_coordinates, coordinates);
            evaluation_shape_district = eval_shape(count_coordinates, coordinates);
            evaluation_map_district = (evaluation_fill_district + evaluation_shape_district)/2;
            evaluation_map_akk += evaluation_map_district;

            //prints the result of a single district to a txt-files
            print_results_to_txt(i, state.grid_map, evaluation_fill_district, evaluation_shape_district);

            count_districts++;

            free(coordinates);
        }
    }

    return evaluation_map_akk/count_districts; //returns the average score of all districts
}

/**
 *
 * @param rows number of rows in the grid-map of the state
 * @param cols number of columns in the grid-map of state
 * @param district grid-map of a district
 * @param district_no the number of the district that is called
 * @param count number of grids in the district
 * @return an array of (x, y) coordinates
 */
coordinate_t* generate_coordinates(int rows, int cols, int** district, int district_no, int* count) {

    *count = 0; // Initialize count of coordinates

    coordinate_t* coordinates = malloc(rows * cols * sizeof(coordinate_t)); // Allocate memory for the coordinates

    // generates coordinates for each point of a district in the 2d array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (district[i][j] == district_no) { // Only add coordinates for non-zero elements
                coordinates[*count].y = i+0.5;
                coordinates[*count].x = j+0.5;
                (*count)++;
            }
        }
    }

    return coordinates; //returns an array of structs containing coordinates for all grids in a district
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

    //sums up the values from each coordinate in the district
    for (int i = 0; i < count; i++) {
        sum_of_x += coordinates[i].x;
        sum_of_y += coordinates[i].y;
    }

    //calculates the average for all coordinates.
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

/**
 * Prints the result and a map of a single district to a txt-file
 * @param district_no The number of the districts that is to be printed
 * @param district a pointer to the 2d array of districts
 * @param eval_fill the score of the district on evaluation of fill
 * @param eval_shape the score of the district on evaluation of shape
 */
void print_results_to_txt(int district_no, int** district, double eval_fill, double eval_shape) {

    char file_name[100] = {"Output_files/eval_map/output_district_"}; //allocates space to store the path to the file

    //combines the path with the district number in a string
    snprintf(file_name, sizeof(file_name), "%s%d.txt", file_name, district_no);

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
       perror("Error opening file");
    }

    //prints the evaluation results from a district
    fprintf(file, "__________________\n");
    fprintf(file, "eval_fill: %lf\n", eval_fill);
    fprintf(file, "eval_shape: %lf\n", eval_shape);
    fprintf(file, "eval_map: %lf\n", (eval_fill+eval_shape)/2);
    fprintf(file, "__________________\n");

    //Print the 2d array of the map where everything outside the district is set to '0'
    fprintf(file, "2D Array:\n");
    for (int i = 0; i < MAX_GRID_SIZE_Y; i++) {
        for (int j = 0; j < MAX_GRID_SIZE_X; j++) {
           if (district[i][j] == district_no) {
               fprintf(file, "%2d ", district[i][j]);
           } else {
               fprintf(file, "0  ");
           }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    }