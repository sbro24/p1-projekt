#include "header.h"
#include "construct_state_header.h"
#include "calculate_proportionality.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_program();
void run_unit_tests();
void test_calc_center();
void test_calc_dist();
int main(void) {

    //run_program();
    run_unit_tests();

    return 0;
}

// write actual program here
void run_program() {

}

// write unit test here
void run_unit_tests() {

    //printf("Fucking cLion AAAAAAAAAAAAAAAAAAAAAAAAAA!\n");

    //char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    //construct_party_array(parties);
    //int number_of_parties = count_parties(parties);

    //county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    //construct_county_array(counties, parties, number_of_parties);
    //int number_of_counties = count_counties_in_struct(counties);

    test_calc_avg_dist();
     test_calc_center();
     test_calc_dist();

    //state_t state = construct_state(counties, parties, number_of_parties);
    //double evaluation_map = eval_map();
    //printf("Evaluation of map form main: %lf\n", evaluation_map);

    //gallagher_index(state);
}

void error_handling(char *message) {
    printf("%s (press ENTER to end process)", message);
    getchar();
    exit(EXIT_FAILURE);
}

