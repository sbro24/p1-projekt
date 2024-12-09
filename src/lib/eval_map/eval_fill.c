//
// Created by mikke on 06-12-2024.
//

#include "eval_map.h"

double eval_fill(int count, coordinate_t coordinates[count]) {
    double radius = calc_radius(count);

    double fill_evaluation = check_coordinate(count, coordinates, radius);

    return fill_evaluation;
}

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