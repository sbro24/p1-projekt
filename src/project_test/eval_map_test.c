#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eval_map.h>


void test_calc_avg_dist() {

    // Expected value
    double expected_avg_dist = 99; // Adjust if necessary

    // Test input in x and y arrays
    int count = 5;
    double x_coords[] = {3.5, 3.5, 4.5, 4.5, 5.5};
    double y_coords[] = {4.5, 5.5, 4.5, 5.5, 4.5};

    // Convert
    coordinate test_coordinates[count];
    for (int i = 0; i < count; i++) {
        test_coordinates[i].x = x_coords[i];
        test_coordinates[i].y = y_coords[i];
    }

    // Calculate the center
    double center_x = 0.0, center_y = 0.0;
    calc_center(&center_x, &center_y, test_coordinates, count);

    printf("Y:%lf\n X:%lf\n", center_y, center_x);

    // Calculate the actual average distance
    double actual_avg_dist = calc_avg_dist(count, test_coordinates, center_x, center_y);

    // Input tolerance
    double tolerance = 0.5;
    if (fabs(expected_avg_dist - actual_avg_dist) <= tolerance) {
        printf("Test passed");
    } else {
        printf("Test failed: Expected = %lf, Actual = %lf\n", expected_avg_dist, actual_avg_dist);
    }
}
