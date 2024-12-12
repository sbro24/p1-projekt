#include <stdio.h>
#include "output.h"
#include "header.h"

// Function that will run in main, which prints out the desired output of the program
void output(state_t state, char parties[MAX_NUMBER_OF_PARTIES][4], double eval_map, double gallagher_index) {
    // Function that calculates and prints vote percentages and seats per party
    output_vote_percentages_and_seats(state, parties);

    // Function that prints the eval_map index
    print_eval_map_index(eval_map);

    // Function that prints the gallagher-index
    print_gallagher_index(gallagher_index);

    // Function that prints the final score
    print_final_score(eval_map, reformat_gallagher_index(gallagher_index));
}

// Function that calculates and prints vote percentages and seats per party
void output_vote_percentages_and_seats(state_t state, char parties[MAX_NUMBER_OF_PARTIES][4]) {
    // Initialize variables
    int total_votes = 0;
    double vote_percentages[MAX_NUMBER_OF_PARTIES] = {0};

    // For loop to count total number of votes in the different districts
    for(int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        // Calculate total votes and seats
        total_votes += state.total_votes[i];
    }

    // For loop to loop through the different districts
    for(int i = 0; i < MAX_NUMBER_OF_PARTIES; i++) {
        // Calculate vote percentages
        vote_percentages[i] = 100.00 * state.total_votes[i] / total_votes;
        if (state.number_of_seats[i] <= 0) continue;
            printf("%s vote percentage: %.2f%\n", parties[i], vote_percentages[i]);
            printf("%s Party seats: %d\n", parties[i], state.number_of_seats[i]);
    }
    printf("\n");
}

// Function that prints the eval_map index
void print_eval_map_index(double eval_map) {

    printf("eval_map: %lf\n", eval_map);
    printf("\n");
}

// Function that prints the gallagher-index
void print_gallagher_index(double gallagher_index) {

    printf("gallagher_index: %lf\n", gallagher_index);
    printf("\n");
}

// Function that reformats the gallagher-index, so that it can be used to calculate a final score
double reformat_gallagher_index(double gallagher_index) {
    gallagher_index = 100.00 - gallagher_index;

    return gallagher_index;
}

// Function that calculates the final score, by finding the mean number
// of the eval_map- and reformated gallagher indexes
double calculate_final_score(double eval_map, double reformated_gallagher_index) {
    double final_score = (eval_map + reformated_gallagher_index) / 2;

    return final_score;
}

// Function that prints the final score
void print_final_score(double eval_map, double reformated_gallagher_index) {
    double final_score = calculate_final_score(eval_map, reformated_gallagher_index);
    printf("final_score: %lf\n", final_score);
}
