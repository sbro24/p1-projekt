#include <stdio.h>
#include <math.h>
#include "calculate_proportionality.h"
#include "header.h"


/* A function that calculates the Gallagher-index of the given state.
 * It has to first sum up the number of votes and seats per party,
 * then it calculates the percentages of votes and seats, and then the difference squared,
 * further, it halves the sum of the difference squared, and finally,
 * it calculates the square root of the half of sum of difference squared,
 * which is the desired Gallagher-index. */
double gallagher_index(state_t state) {
    // Initialize variables
    int total_votes = 0;
    int total_seats = 0;
    double vote_percentages[MAX_NUMBER_OF_PARTIES] = {0};
    double seat_percentages[MAX_NUMBER_OF_PARTIES] = {0};
    double difference_squared[MAX_NUMBER_OF_PARTIES] = {0};
    double half_of_sum_of_difference_squared = 0;

    // For loop to count total number of votes and seats in the different districts
    for(int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        // Calculate total votes and seats
        total_votes += state.total_votes[i];
        total_seats += state.number_of_seats[i];
    }

    // For loop to loop through the different districts
    for(int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {

        // Calculate vote and seat percentages
        vote_percentages[i] = 100.00 * state.total_votes[i] / total_votes;
        seat_percentages[i] = 100.00 * state.number_of_seats[i] / total_seats;

        // Calculate the difference between vote and seat percentages, then squared
        difference_squared[i] = pow(vote_percentages[i] - seat_percentages[i], 2);

        // Halve the sum of the squared difference
        half_of_sum_of_difference_squared += difference_squared[i] / 2;
    }
    // Square root of the halved sum is the desired Gallagher-Index
    double gallagher_index = sqrt(half_of_sum_of_difference_squared);

    return gallagher_index;
}



