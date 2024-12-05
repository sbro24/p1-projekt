#include "header.h"
#include "construct_state_header.h"
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

    printf("Number of parties: %d\n", number_of_counties);

    //state_t state = construct_state();

    double evaluation_map = eval_map();
    printf("Evaluation of map form main: %lf\n", evaluation_map);

    return 0;
}

void error_handling(char *message) {
    printf("%s (press ENTER to end prosess)", message);
    getchar();
    exit(EXIT_FAILURE);
}

