#include "eval_map.h"

/**
 * evaluates fill of a district
 * @param count number of coordinates in grid-map of a given district
 * @param coordinates array of coordinates in a given district
 * @return an index between 0 and 100
 */
double eval_fill(int count, coordinate_t coordinates[count]) {
    double radius = calc_radius(count);
    double fill_evaluation = check_coordinate(count, coordinates, radius);

    return fill_evaluation;
}

/**
 * calculates the percentage of coordinates within a circle
 * @param count number of coordinates in grid-map of a given district
 * @param coordinates array of coordinates in a given district
 * @param radius radius of the smallest possible circle containing the number of coordinates
 * @return a percentage between 0 and 100
 */
double check_coordinate(int count, coordinate_t coordinates[count], double radius) {

    int count_in_circle = 0; //counts the number of coordinates within the circle
    double dist = 0;

    double  center_x = 0,
            center_y = 0;

    //calculates the center of the district and assigns them to center-x and center-y
    calc_center(&center_x, &center_y, coordinates, count);

    //checks if coordinates is within the circle and counts up either in or out of circle
    for (int i = 0; i < count; i++) {
        coordinate_t coordinate_point = {coordinates[i].x, coordinates[i].y};
        dist = calc_dist(&coordinate_point, center_x, center_y);
        if (dist < radius) {
            count_in_circle++;
        }
    }

    //returns the percentage of coordinates within the circle
    return (double) count_in_circle/count*100;

}