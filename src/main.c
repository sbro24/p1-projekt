#include "header.h"
#include "construct_state_header.h"
#include "calculate_proportionality.h"
#include "eval_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include <gallagher_index_test_2.c>

void run_program();
void run_unit_tests();


int main(void) {

    run_program();
    run_unit_tests();

    return 0;
}

// write actual program here
void run_program() {
    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_party_array(parties);
    int number_of_parties = count_parties(parties);

    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    construct_county_array(counties, parties, number_of_parties);
    int number_of_counties = count_counties_in_struct(counties);

    state_t state = construct_state(counties, parties, number_of_parties);
    double evaluation_map = eval_map(MAX_NUMBER_OF_DISTRICTS, state.districts);
    printf("Evaluation of map from main: %lf\n", evaluation_map);

    gallagher_index(state);
}

// write unit test here
void run_unit_tests() {


    //dataimport_test()
    //test_calc_avg_dist();
    //test_calc_center();
    //test_calc_dist();
    //test_eval_fill();
    //test_gallagher_index();


}

void error_handling(char *message) {
    printf("%s (press ENTER to end process)", message);
    getchar();
    exit(EXIT_FAILURE);
}

