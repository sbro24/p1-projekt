#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x; // Row index
    double y; // Column index
} coordinate;

//prototypes
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


int
main(void) {

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

    return 0;
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

    int temp_2 [10][10] = { {0,0,0,1,1,1,0,0,0,0},
                            {0,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,0,0,0},
                            {0,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,0,0},
                            {0,0,1,1,1,1,1,1,1,1},
                            {0,0,1,1,1,1,1,1,1,0},
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,1,1,1,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0}};

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
            district[i][j] = temp_3[i][j];
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

double eval_shape(int count, coordinate coordinates[count]) {

    double  center_x = 0,
            center_y = 0;

    calc_center(&center_x, &center_y, coordinates, count);
    double shape_evaluation = calc_avg_dist(count, coordinates, center_x, center_y);

    return shape_evaluation;
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

    double avg_dist = dist/count;
    double optimal_dist = (calc_radius(count)*2)/3;

    return optimal_dist/avg_dist*100;
}

double calc_dist (coordinate* coordinate_point, double center_x, double center_y) {

    double dist_x = (double) coordinate_point[0].x - center_x;
    double dist_y = (double) coordinate_point[0].y - center_y;

    double dist = sqrt(dist_x*dist_x + dist_y*dist_y);

    return dist;
}

double eval_fill(int count, coordinate coordinates[count]) {
    double radius = calc_radius(count);

    double fill_evaluation = check_coordinate(count, coordinates, radius);

    return fill_evaluation;
}

double calc_radius (int count) {
    return sqrt(count / (M_PI));
}

double check_coordinate(int count, coordinate coordinates[count], double radius) {

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

    return (double) in_cirkle/(out_cirkle+in_cirkle)*100;

}
