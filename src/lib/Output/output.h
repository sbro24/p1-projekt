
#ifndef OUTPUT_H
#define OUTPUT_H

#include "header.h"

void output(state_t state, char parties[MAX_NUMBER_OF_PARTIES][4], double eval_map, double gallagher_index);

void output_vote_percentages_and_seats(state_t state, char parties[MAX_NUMBER_OF_PARTIES][4]);

void print_eval_map_index(double eval_map);

double reformat_gallagher_index(double gallagher_index);

void print_gallagher_index(double gallagher_index);

double calculate_final_score(double eval_map, double reformated_gallagher_index);

void print_final_score(double eval_map, double reformated_gallagher_index);


#endif //OUTPUT_H
