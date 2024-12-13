#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eval_map.h>
#include <string.h>

#include "header.h"

/**
 * An evaluation of the state map in terms of fill and distance to center
 * @param no_of_districts the total number of districts in state
 * @param districts array of district structs containing grid-maps
 * @return  an index between 0 and 100
 */
double eval_map(int no_of_districts, state_t* state) {

    district_test_t districts_test[2];

    create_district(2, districts_test);
    read_map_district(2, districts_test);
    read_map_to_district(2, districts_test);

    int count = 0;
    coordinate_t* coordinates = NULL; //initialization of array of structs containing coordinates.
    coordinates = generate_coordinates(MAX_GRID_SIZE_Y, MAX_GRID_SIZE_X, districts_test[1].map, &count);

    double  evaluation_fill = 0,
            evaluation_fill_akk = 0,
            evaluation_shape = 0,
            evaluation_shape_akk = 0,
            evaluation_map = 0,
            evaluation_map_akk = 0;

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
        /*
        district_t district_copy[MAX_NUMBER_OF_DISTRICTS];
        for (int i = 0; i < MAX_NUMBER_OF_DISTRICTS; i++) {
            district_copy[i] = districts[i];
        }

        coordinate_t* coordinates = NULL; //initialization of array of structs containing coordinates.

        double  evaluation_fill = 0,
                evaluation_fill_akk = 0,
                evaluation_shape = 0,
                evaluation_shape_akk = 0,
                evaluation_map = 0,
                evaluation_map_akk = 0;

        // for each districts fill and shape is evaluated. Result are summed up as akkumulated values.
        for (int i = 0; i < no_of_districts; i++) {
            int count = 0; // To store the number of coordinates generated
            coordinates = generate_coordinates(MAX_GRID_SIZE_X, MAX_GRID_SIZE_Y, districts[i].grid_map, &count);
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



        printf("2D Array:\n");
        for (int i = 0; i < MAX_GRID_SIZE_Y; i++) {
            for (int j = 0; j < MAX_GRID_SIZE_X; j++) {
                printf(" %d ", districts_test[1].map[i][j]);
            }
            printf("\n");
        }
*/

    FILE *file = fopen("output_district_1.txt", "w");
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

coordinate_t* generate_coordinates(int rows, int cols, int district[rows][cols], int* count) {

    *count = 0; // Initialize count

    // Allocate memory for the coordinates (worst case: every element has a coordinate)
    coordinate_t* coordinates = malloc(rows * cols * sizeof(coordinate_t));

    // Traverse the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (district[i][j] != 0) { // Only add coordinates for non-zero elements
                coordinates[*count].y = i+0.5;
                coordinates[*count].x = j+0.5;
                (*count)++;
            }
        }
    }

    return coordinates;
}


/**
 * prints a grid-map of district
 * @param district grid-map of a district as a 2d array
 */

/*
void print_district (int district[47][118]) {

    printf("Map: \n");
    printf("___________________________________\n");
    for (int i = 0; i<47; i++) {
        for(int j = 0; j<118; j++) {
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
*/

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

district_test_t* create_district(int no_of_districts, district_test_t districts[no_of_districts]) {
    char district_name[2][30] =     {
        {"district1"},
        {"district2"},
    };

    for (int i = 0; i<no_of_districts; i++) {
        districts[i].id = i;
        strcpy(districts[i].name, district_name[i]);
        districts[i].votes[0] = 0;
        districts[i].votes [1]= 0;
    }

    return districts;
}

district_test_t *read_map_district(int no_of_districts, district_test_t districts[no_of_districts]) {
    char filename[] = "src/input_files/grid_north_carolina_correctID.txt"; // Path to your text file
    int array[MAX_GRID_SIZE_Y][MAX_GRID_SIZE_X]; // Fixed size array
    int rows = 0, cols = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char line[2048];
    while (fgets(line, sizeof(line), file) && rows < MAX_GRID_SIZE_Y) {
        cols = 0;
        char *token = strtok(line, "\t");
        while (token != NULL && cols < MAX_GRID_SIZE_X) {
            array[rows][cols] = atoi(token); // Convert string to integer
            token = strtok(NULL, "\t");    // Move to the next token
            cols++;
        }
        rows++;
    }

    fclose(file);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                districts[i].map[j][k] = array[j][k];
            }
        }
    }

    return districts;
}

void read_map_to_district(int no_of_districts, district_test_t districts_test[no_of_districts]) {

    int count = 0;

    for (int j = 0; j < MAX_GRID_SIZE_Y; j++) {
        for (int k = 0; k < MAX_GRID_SIZE_X; k++) {
            if (districts_test[0].map[j][k] != 0 &&
                districts_test[0].map[j][k] == 8 ||
                districts_test[0].map[j][k] == 16 ||
                districts_test[0].map[j][k] == 23 ||
                districts_test[0].map[j][k] == 30 ||
                districts_test[0].map[j][k] == 36 ||
                districts_test[0].map[j][k] == 41 ||
                districts_test[0].map[j][k] == 43 ||
                districts_test[0].map[j][k] == 45 ||
                districts_test[0].map[j][k] == 49 ||
                districts_test[0].map[j][k] == 53 ||
                districts_test[0].map[j][k] == 61 ||
                districts_test[0].map[j][k] == 65 ||
                districts_test[0].map[j][k] == 73 ||
                districts_test[0].map[j][k] == 75 ||
                districts_test[0].map[j][k] == 79 ||
                districts_test[0].map[j][k] == 81 ||
                districts_test[0].map[j][k] == 101 ||
                districts_test[0].map[j][k] == 103 ||
                districts_test[0].map[j][k] == 107 ||
                districts_test[0].map[j][k] == 108 ||
                districts_test[0].map[j][k] == 110 ||
                districts_test[0].map[j][k] == 112
                )

                {
                districts_test[1].map[j][k] = 1;
                count++;
            } else {
                districts_test[1].map[j][k] = 0;
            }
        }
    }

}
