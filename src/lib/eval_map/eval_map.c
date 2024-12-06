#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eval_map.h>

double eval_map(void) {



    int district[10][10];
    int count = 0; // To store the number of coordinates generated

    read_district(district);
    coordinate* coordinates = generate_coordinates(10, 10, district, &count);

    print_district(district);

    double evaluation_fill = eval_fill(count, coordinates);
    double evaluation_shape = eval_shape(count, coordinates);

    double evaluation_map = (evaluation_fill + evaluation_shape)/2;

        printf("fill evaluation: %lf\n", evaluation_fill);
        printf("Shape evaluation: %lf\n", evaluation_shape);
        printf("map evaluation (overall score): %lf\n", evaluation_map);

    free(coordinates);

    return evaluation_map;
}

void read_district (int district[10][10]) {
    int temp_1 [10][10] = {{1,1,1,1,1,1,1,1,1,1},
                        {0,1,1,1,1,1,1,0,0,0},
                        {0,0,1,1,1,1,1,0,0,0},
                        {0,1,1,1,1,1,1,0,0,0},
                        {0,0,1,1,1,1,1,1,0,0},
                        {0,0,1,1,1,0,0,0,0,0},
                        {0,0,1,1,1,1,1,1,1,0},
                        {0,0,0,1,1,1,1,0,0,0},
                        {0,0,0,1,1,1,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0}};

    int temp_2 [10][10] = { {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}};

    int temp_3 [10][10] = { {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,0,0},
                            {0,1,1,1,1,1,1,1,1,0},
                            {1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1},
                            {0,1,1,1,1,1,1,1,1,0},
                            {0,0,1,1,1,1,1,1,0,0},
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0}};

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            district[i][j] = temp_1[i][j];
        }
    }
}

coordinate* generate_coordinates(int rows, int cols, int district[rows][cols], int* count) {
    *count = 0; // Initialize count

    // Allocate memory for the coordinates (worst case: every element has a coordinate)
    coordinate* coordinates = malloc(rows * cols * sizeof(coordinate));
    if (!coordinates) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

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

void print_district (int district[10][10]) {

    printf("Map: \n");
    printf("___________________________________\n");
    for (int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++) {
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

void calc_center (double* center_x, double* center_y, coordinate* coordinates, int count) {
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


