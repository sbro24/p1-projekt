#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x; // Row index
    int y; // Column index
} coordinate;

//prototypes
void read_district (int district[10][10]);
void print_district (int district[10][10]);
coordinate* generate_coordinates(int rows, int cols, int district[rows][cols], int* count);

double eval_fill(int count, coordinate coordinates[count]);
    double calc_radius (int count);
    void check_coordinate(int count, coordinate coordinates[count], double radius);

double eval_shape(int count, coordinate coordinates[count]);
    double calc_dist (coordinate* coordinate_point, double center_x, double center_y);
    double calc_avg_dist(int count, coordinate coordinates[count], double center_x, double center_y);
    void calc_center (double* center_x, double* center_y, coordinate* coordinates, int count);

int
main(void) {

    int district[10][10];
    int count = 0; // To store the number of coordinates generated

    read_district(district);
    coordinate* coordinates = generate_coordinates(10, 10, district, &count);
    print_district(district);

    eval_fill(count, coordinates);
    eval_shape(count, coordinates);

    free(coordinates);

    return 0;
}

void read_district (int district[10][10]) {
    int temp [10][10] = {{0,0,0,1,1,1,0,0,0,0},
                        {0,1,1,1,1,1,1,0,0,0},
                        {0,0,1,1,1,1,1,0,0,0},
                        {0,1,1,1,1,1,1,0,0,0},
                        {0,0,1,1,1,1,1,1,0,0},
                        {0,0,1,1,1,1,1,1,1,0},
                        {0,0,1,1,1,1,1,1,1,0},
                        {0,0,0,1,1,1,1,0,0,0},
                        {0,0,0,1,1,1,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0}};

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            district[i][j] = temp[i][j];
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
                coordinates[*count].x = i;
                coordinates[*count].y = j;
                (*count)++;
            }
        }
    }

    return coordinates;
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


double eval_shape(int count, coordinate coordinates[count]) {

    double  center_x = 0,
            center_y = 0;

    calc_center(&center_x, &center_y, coordinates, count);
    double average_dist = calc_avg_dist(count, coordinates, center_x, center_y);
    printf("average dist: %lf\n", average_dist);

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

double calc_avg_dist(int count, coordinate coordinates[count], double center_x, double center_y) {
    double dist = 0;

    for (int i = 0; i < count; i++) {
        coordinate coordinate_point = {coordinates[i].x, coordinates[i].y};
        dist += calc_dist (&coordinate_point, center_x, center_y);
    }

    return dist/count;
}

double calc_dist (coordinate* coordinate_point, double center_x, double center_y) {

    double dist_x = (double) coordinate_point[0].x - center_x;
    double dist_y = (double) coordinate_point[0].y - center_y;

    double dist = sqrt(dist_x*dist_x + dist_y*dist_y);

    return dist;
}



double eval_fill(int count, coordinate coordinates[count]) {
    double radius = calc_radius(count);
    printf("Radius: %lf\n", radius);

    check_coordinate(count, coordinates, radius);
}

double calc_radius (int count) {
    return sqrt(count / (M_PI));
}

void check_coordinate(int count, coordinate coordinates[count], double radius) {

    int in_cirkle = 0;
    int out_cirkle = 0;
    double dist = 0;

    double  center_x = 0,
            center_y = 0;

    calc_center(&center_x, &center_y, coordinates, count);

    for (int i = 0; i < count; i++) {
        coordinate coordinate_point = {coordinates[i].x, coordinates[i].y};
        dist = calc_dist(&coordinate_point, center_x, center_y);
        if (dist < radius) {
            in_cirkle++;
        } else {
            out_cirkle++;
        }
    }
    printf("in cirkle: %d\n", in_cirkle);
    printf("out cirkle: %d\n", out_cirkle);

}










