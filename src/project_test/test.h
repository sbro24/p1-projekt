//
// Created by mikke on 06-12-2024.
//

#ifndef TEST_H
#define TEST_H

state_t test_construct_state(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties);
void test_construct_county_array(county_t counties[MAX_NUMBER_OF_COUNTIES], char parties[MAX_NUMBER_OF_PARTIES][4], int number_of_parties);
void construct_test_party_array(char parties[MAX_NUMBER_OF_PARTIES][4]);
void dataimport_test_output(void);
void output_to_txt2();
//void output_to_txt(const char *test_output);
void dataimport_test(void);
void test_calc_avg_dist(void);
void test_calc_center();
void test_calc_dist();
void test_eval_fill();
void test_gallagher_index();
#endif //TEST_H
