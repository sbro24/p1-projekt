#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x; // Row index
    int y; // Column index
} coordinate;

double calc_radius (int count);
void read_district (int district[10][10]);
void print_district (int district[10][10]);
coordinate* generate_coordinates(int rows, int cols, int district[rows][cols], int* count);
void calc_center (double* center_x, double* center_y, coordinate* coordinates, int count);
double calc_dist (coordinate* coordinate_point, double center_x, double center_y);

int main(void) {

    int district[10][10];

    read_district(district);
    print_district(district);

    int count = 0; // To store the number of coordinates generated
    coordinate* coordinates = generate_coordinates(10, 10, district, &count);

    double  center_x = 0,
            center_y = 0;

    calc_center(&center_x, &center_y, coordinates, count);

    printf("Center x: %lf\n", center_x);
    printf("Center y: %lf\n", center_y);

    double radius = calc_radius(count);

    coordinate point = {coordinates[1].x, coordinates[1].y};

    printf("X: %d, Y: %d\n", coordinates[1].x, coordinates[1].y);

    double dist = calc_dist(&point, center_x, center_y);
    printf("Distance: %lf\n", dist);

    free(coordinates);

    return 0;
}

double calc_dist (coordinate* coordinate_point, double center_x, double center_y) {

    double dist_x = (double) coordinate_point[0].x - center_x;
    double dist_y = (double) coordinate_point[0].y - center_y;
    printf("Dist x: %lf", dist_x);
    printf("Dist y: %lf", dist_y);

    return sqrt(dist_x*dist_x + dist_y*dist_y);
}

double calc_radius (int count) {
    return sqrt(count / (2 * M_PI));
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
                coordinates[*count].x = i;
                coordinates[*count].y = j;
                (*count)++;
            }
        }
    }

    return coordinates;
}

void calc_center (double* center_x, double* center_y, coordinate* coordinates, int count) {
    int sum_of_x = 0;
    int sum_of_y = 0;

    for (int i = 0; i < count; i++) {
        sum_of_x += coordinates[i].x;
        sum_of_y += coordinates[i].y;
    }

    *center_x = (double) sum_of_x/count;
    *center_y = (double) sum_of_y/count;
}

void read_district (int district[10][10]) {
    int temp [10][10] = {{0,0,1,0,0,0,0,0,0,0},
                        {0,1,1,1,0,0,0,0,0,0},
                        {0,0,1,1,1,0,0,0,0,0},
                        {0,1,1,1,1,1,1,0,0,0},
                        {0,0,1,1,1,1,1,1,0,0},
                        {0,0,1,1,1,1,1,1,1,0},
                        {0,0,1,1,1,1,1,1,1,0},
                        {1,1,1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1,0,0},
                        {1,1,1,1,1,1,1,1,0,0}};

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            district[i][j] = temp[i][j];
        }
    }
}

void print_district (int district[10][10]) {
    for (int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++) {
            if (district[i][j] == 1 ) {
                printf("%d", district[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}