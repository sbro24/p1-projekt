//
// Created by mikke on 06-12-2024.
//

#include "eval_map.h"
#include <math.h>
#include <stdio.h>

double eval_shape(int count, coordinate_t coordinates[count]) {

    double  center_x = 0,
            center_y = 0;

    calc_center(&center_x, &center_y, coordinates, count);

    double shape_evaluation = calc_avg_dist(count, coordinates, center_x, center_y);

    return shape_evaluation;
}

double calc_avg_dist(int count, coordinate_t coordinates[count], double center_x, double center_y) {
    double dist = 0;

    for (int i = 0; i < count; i++) {
        coordinate_t coordinate_point = {coordinates[i].x, coordinates[i].y};
        dist += calc_dist (&coordinate_point, center_x, center_y);
    }

    double avg_dist = dist/count;
    double optimal_dist = (calc_radius(count)*2)/3;

    return optimal_dist/avg_dist*100;
}

double calc_dist (coordinate_t* coordinate_point, double center_x, double center_y) {

    double dist_x = (double) coordinate_point[0].x - center_x;
    double dist_y = (double) coordinate_point[0].y - center_y;

    double dist = sqrt(dist_x*dist_x + dist_y*dist_y);

    return dist;
}