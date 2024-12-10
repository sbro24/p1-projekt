//
// Created by mikke on 06-12-2024.
//

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

    int in_cirkle = 0;
    int out_cirkle = 0;
    double dist = 0;

    double  center_x = 0,
            center_y = 0;

    calc_center(&center_x, &center_y, coordinates, count);

    for (int i = 0; i < count; i++) {
        coordinate_t coordinate_point = {coordinates[i].x, coordinates[i].y};
        dist = calc_dist(&coordinate_point, center_x, center_y);
        if (dist < radius) {
            in_cirkle++;
        } else {
            out_cirkle++;
        }
    }

    return (double) in_cirkle/(out_cirkle+in_cirkle)*100;

}