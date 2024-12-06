#include "header.h"
#include "construct_state_header.h"
#include "calculate_proportionality.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //printf("Fucking cLion AAAAAAAAAAAAAAAAAAAAAAAAAA!\n");

    char parties[MAX_NUMBER_OF_PARTIES][4] = {""};
    construct_party_array(parties);
    int number_of_parties = count_parties(parties);

    county_t counties[MAX_NUMBER_OF_COUNTIES] = {{0, "", 0, {0},{0}}};
    construct_county_array(counties, parties, number_of_parties);
    int number_of_counties = count_counties_in_struct(counties);

    state_t state = construct_state(counties, parties, number_of_parties);

    //double evaluation_map = eval_map();
    //printf("Evaluation of map form main: %lf\n", evaluation_map);

    gallagher_index(state);

    return 0;
}

void error_handling(char *message) {
    printf("%s (press ENTER to end process)", message);
    getchar();
    exit(EXIT_FAILURE);
}

