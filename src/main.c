#include "header.h"
#include "construct_state_header.h"
#include "calculate_proportionality.h"
#include "eval_map.h"
#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include <gallagher_index_test_2.c>

void run_program();
void run_unit_tests();


int main(void) {
    if (test_prompt() == 'y') run_unit_tests();
    run_program();

    return 0;
}

void run_program() {
    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_party_array(parties);

    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    construct_county_array(counties, parties, count_parties(parties));

    state_t state = construct_state(counties, parties, count_parties(parties));

    output(state, parties, eval_map(state), gallagher_index(state));
}

// write unit test here
void run_unit_tests() {

    //formatting
    printf("----------------------------------------------------------");
    printf("\nTest results:\n\n");
    test_calc_avg_dist();
    test_calc_center();
    test_calc_dist();
    test_eval_fill();
    test_gallagher_index();
    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_test_party_array(parties);
    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    test_construct_county_array(counties, parties, count_parties(parties));
    test_construct_state(counties, parties, count_parties(parties));
}

char test_prompt() {
    printf("Do you wish to run tests before the program? (y/n)\n");
    char result;
    while (1) {
        scanf("%c", &result);
        if (result == 'y' || result == 'n') return result;
        printf("Invalid input! Do you wish to run tests before the program? (y/n)\n");
    }
}



