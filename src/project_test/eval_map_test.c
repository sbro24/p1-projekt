#include "lib/eval_map/eval_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

//Unit test 1
void test_calc_avg_dist() {

    // Expected value
    double expected_avg_dist = 99; // Adjust if necessary

    // Test input in x and y arrays
    int count = 5;
    double x_coords[] = {3.5, 3.5, 4.5, 4.5, 5.5};
    double y_coords[] = {4.5, 5.5, 4.5, 5.5, 4.5};

    // Convert
    coordinate_t test_coordinates[count];
    for (int i = 0; i < count; i++) {
        test_coordinates[i].x = x_coords[i];
        test_coordinates[i].y = y_coords[i];
    }

    printf("Test for calc_avg_dist:\n");
    // Calculate the center
    double center_x = 0.0, center_y = 0.0;
    calc_center(&center_x, &center_y, test_coordinates, count);

    printf("Y:%lf\nX:%lf\n", center_y, center_x);

    // Calculate the actual average distance
    double actual_avg_dist = calc_avg_dist(count, test_coordinates, center_x, center_y);

    // Input tolerance
    double tolerance = 0.5;
    if (fabs(expected_avg_dist - actual_avg_dist) <= tolerance) {
        printf("Test passed\n\n");
    } else {
        printf("Test failed: Expected = %lf, Actual = %lf\n\n", expected_avg_dist, actual_avg_dist);
    }
}

//Unit test 2
void test_calc_center() {
    // Test input
    int count = 5;
    double x_coords[] = {3.5, 3.5, 4.5, 4.5, 5.5};
    double y_coords[] = {4.5, 5.5, 4.5, 5.5, 4.5};

    //Convert
    coordinate_t test_coordinates[count];
    for (int i = 0; i < count; i++) {
        test_coordinates[i].x = x_coords[i];
        test_coordinates[i].y = y_coords[i];
    }

    // Expected values
    double expected_center_x = 4.3; // Mean of {1.0, 2.0, 3.0, 4.0, 5.0}
    double expected_center_y = 4.9; // Mean of {2.0, 3.0, 4.0, 5.0, 6.0}

    // Actual values
    double actual_center_x = 0.0, actual_center_y = 0.0;

    // Calculate the center
    calc_center(&actual_center_x, &actual_center_y, test_coordinates, count);


    printf("Test for calc_center:\n");
    printf("Expected Center: (%.2f, %.2f)\n", expected_center_x, expected_center_y);
    printf("Actual Center: (%.2f, %.2f)\n", actual_center_x, actual_center_y);

    // Verify the result
    double tolerance = 0.1;
    if (fabs(expected_center_x - actual_center_x) <= tolerance &&
        fabs(expected_center_y - actual_center_y) <= tolerance) {
        printf("Test passed\n\n");
        } else {
            printf("Test failed\n");
        }
}

//Unit test 3

void test_calc_dist() {

    // Test input
    coordinate_t test_coordinates = {3.5, 4.5}; // Example point
    double center_x = 4.3, center_y = 4.9; // Example center coordinates

    // Actual distance
    double actual_dist = calc_dist(&test_coordinates, center_x, center_y);

    // Expected distance
    double expected_dist = 0.89;


    printf("Test for calc_dist:\n");
    printf("Expected Distance: %.2f\n", expected_dist);
    printf("Actual Distance: %.2f\n", actual_dist);

    // Verify the result
    double tolerance = 0.1;
    if (fabs(expected_dist - actual_dist) <= tolerance) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
}

void test_eval_fill() {

    // Expected value for eval_fill function
    double expected_eval_fill = 80; // Adjust if necessary

    // Test input in x and y arrays
    int count = 5;
    double x_coords[] = {3.5, 3.5, 4.5, 4.5, 5.5};
    double y_coords[] = {4.5, 5.5, 4.5, 5.5, 4.5};

    // Convert
    coordinate_t test_coordinates[count];
    for (int i = 0; i < count; i++) {
        test_coordinates[i].x = x_coords[i];
        test_coordinates[i].y = y_coords[i];
    }

    // calculate the actual values for eval_fill
    double actual_eval_fill = eval_fill(count, test_coordinates);

    printf("\nTest for eval_fill:\n");
    printf("Expected Distance: %.2f\n", expected_eval_fill);
    printf("Actual Distance: %.2f\n", actual_eval_fill);

    // Verify the result
    double tolerance = 0.1;
    if (fabs(expected_eval_fill - actual_eval_fill) <= tolerance) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

  }