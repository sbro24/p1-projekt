#include "lib/calculate_proportionality/calculate_proportionality.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

// Unit test 1: Gallagher Index


void test_gallagher_index() {
    // Initialize variables
    int total_votes = 0;
    int total_seats = 0;
    double vote_percentages[5] = {0};
    double seat_percentages[5] = {0};
    double difference_squared[5] = {0};
    double half_of_sum_of_difference_squared = 0;

    // Test state struct
    typedef struct {
        // Provide values to test_number_of_seats and test_total_votes for testing
        int test_number_of_seats[5];
        int test_total_votes[5];
    } test_state_t;

    test_state_t test_state = {{3, 7, 6, 10, 15}, 100,
        200, 300, 400, 500};

    for (int i = 0; i < 5; i++) {
        // Calculate total votes and seats
        total_votes += test_state.test_total_votes[i];

        total_seats += test_state.test_number_of_seats[i];
    }

    // For loop to loop through the different districts
    for(int i = 0; i < 5; i++) {
        // Calculate vote and seat percentages
        vote_percentages[i] = 100.00 * test_state.test_total_votes[i] / total_votes;

        seat_percentages[i] = 100.00 * test_state.test_number_of_seats[i] / total_seats;

        // Calculate the difference between vote and seat percentages, then squared
        difference_squared[i] = pow(vote_percentages[i] - seat_percentages[i], 2);

        // Halve the sum of the squared difference
        half_of_sum_of_difference_squared += difference_squared[i] / 2;
    }
    // Square root of the halved sum is the desired Gallagher-Index
    double gallagher_index = sqrt(half_of_sum_of_difference_squared);
    printf("\n gallagher index = %lf\n", gallagher_index);
}