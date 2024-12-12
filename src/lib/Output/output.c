#include <stdio.h>
#include "output.h"
#include "header.h"


void output(state_t state, char parties[MAX_NUMBER_OF_PARTIES][4], double eval_map, double gallagher_index) {
    output_vote_percentages_and_seats(state, parties);
    output_eval_map(eval_map);
    output_gallagher_index(gallagher_index);
    output_final_score(eval_map, reformat_gallagher_index(gallagher_index));
}

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

void output_eval_map(double eval_map) {

    printf("eval_map: %lf\n", eval_map);
    printf("\n");
}

double reformat_gallagher_index(double gallagher_index) {
    gallagher_index = 100.00 - gallagher_index;

    return gallagher_index;
}

void output_gallagher_index(double gallagher_index) {

    printf("gallagher_index: %lf\n", gallagher_index);
    printf("\n");
}

double calculate_final_score(double eval_map, double gallagher_index) {
    double final_score = (eval_map + gallagher_index) / 2;

    return final_score;
}

void output_final_score(double eval_map, double gallagher_index) {
    double final_score = calculate_final_score(eval_map, gallagher_index);
    printf("final_score: %lf\n", final_score);
}
