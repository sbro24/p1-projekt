#include "eval_map.h"
#include <math.h>

/**
 * evaluates shape of a district
 * @param count number of coordinates in grid-map of a given district
 * @param coordinates array of coordinates in a given district
 * @return an index between 0 and 100
 */
double eval_shape(int count, coordinate_t coordinates[count]) {

    double  center_x = 0, //the x-coordinate of the center of the circle
            center_y = 0; //the y-coordinate of the center of the circle

    //calculates the center of the district and assigns them to center-x and center-y
    calc_center(&center_x, &center_y, coordinates, count);

    double avg_dist = calc_avg_dist(count, coordinates, center_x, center_y);
    double optimal_dist = calc_radius(count)*2/3;


    return optimal_dist/avg_dist*100;
}

/**
 * calculates average distance between center and coordinates of a districts relative to the smallest possible average distance
 * @param count evaluates shape of a district
 * @param coordinates number of coordinates in grid-map of a given district
 * @param center_x the center of the district
 * @param center_y the center of the district
 * @return a percentage between 0 and 100
 */
double calc_avg_dist(int count, coordinate_t coordinates[count], double center_x, double center_y) {

    double dist = 0; //the accumulated distance from coordinates to center

    //calculates and accumulates distance from center of a circle to the coordinates in the district
    for (int i = 0; i < count; i++) {
        coordinate_t coordinate_point = {coordinates[i].x, coordinates[i].y};
        dist += calc_dist (&coordinate_point, center_x, center_y);
    }

    return dist/count; //returns the average distance
}

/**
 * calculates the distance from a coordinate to the center of a district using the pythagorean theorem
 * @param coordinate_point a given coordinate within the district
 * @param center_x Center of the district
 * @param center_y Center of the district
 * @return distance
 */
double calc_dist (coordinate_t* coordinate_point, double center_x, double center_y) {
    double dist_x = (double) coordinate_point[0].x - center_x;
    double dist_y = (double) coordinate_point[0].y - center_y;

    //calculates the distance through use of the Pythagorean theorem
    double dist = sqrt(dist_x*dist_x + dist_y*dist_y);

    return dist;
}