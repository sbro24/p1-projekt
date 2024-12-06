#include <stdio.h>
#include <math.h>
#include "calculate_proportionality.h"
#include "header.h"

double gallagher_index(state_t state) {
    int total_votes = 0;
    int total_seats = 0;
    double vote_percentages[MAX_NUMBER_OF_PARTIES] = {0};
    double seat_percentages[MAX_NUMBER_OF_PARTIES] = {0};
    double difference_squared[MAX_NUMBER_OF_PARTIES] = {0};
    double half_of_sum_of_difference_squared = 0;


    for(int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        // Calculate
        total_votes += state.total_votes[i];
        total_seats += state.number_of_seats[i];
        vote_percentages[i] = 100.00 * state.total_votes[i] / total_votes;
        seat_percentages[i] = 100.00 * state.number_of_seats[i] / total_seats;
        difference_squared[i] = pow(vote_percentages[i] - seat_percentages[i], 2);
        half_of_sum_of_difference_squared += difference_squared[i] / 2;
    }
    double gallagher_index = sqrt(half_of_sum_of_difference_squared);

    return gallagher_index;
}
