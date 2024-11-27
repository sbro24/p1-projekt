#include <stdio.h>
#include <stdlib.h>
#include <header.h>
#include <string.h>

#define TOTAL_VOTES 5217905;
#define DEM_TOTAL_VOTES 2328248;
#define REP_TOTAL_VOTES 2889657;
#define OTHER_TOTAL_VOTES 0;

typedef struct  {
    int district_number;
    int total_votes;
    int dem_votes;
    int rep_votes;
    int other_votes;
} district_t;

typedef struct {
    double dem_vote_percentage;
    double rep_vote_percentage;
    double other_vote_percentage;
} vote_percentage_t;


vote_percentage_t calculate_district(district_t district, int total_seats);

void print_district(district_t district, vote_percentage_t vote_result);

vote_percentage_t calculate_percentages(district_t district, int total_seats) {
    // Input the values from district
    double dem_votes = district.dem_votes;
    double rep_votes = district.rep_votes;
    double other_votes = district.other_votes;

    // Calculate the voting percentages
    for (int i = 0; i < total_seats; i++) {
        vote_percentage_t vote_percentage;
        vote_percentage.dem_vote_percentage = 100 * dem_votes / TOTAL_VOTES;
        vote_percentage.rep_vote_percentage = 100 * rep_votes / TOTAL_VOTES;
        vote_percentage.other_vote_percentage = 100 * other_votes / TOTAL_VOTES;
    }

}

void print_district(district_t district, vote_percentage_t vote_results) {
    // Input the values from district

    printf("District %d:\n", district.district_number);
    printf("District total votes: %d\n", district.total_votes);
    printf("District votes for democrats: %d\n", district.dem_votes);
    printf("District votes for republicans: %d\n",district.rep_votes);
    printf("District votes for other parties: %d\n'", district.other_votes);
    printf("\n");

    printf("Democratic total vote percentage: %d:\n", );
}


int main(void) {
    district_t districts[] = {
        {1, 354523, 214596, 139927, 0},
        {2, 314054,140651, 173403, 0}
    };
    int number_of_districts = sizeof(districts) / sizeof(districts[0]);
    int total_seats = number_of_districts;

    for (int i = 0; i < number_of_districts; i++) {
        vote_percentage_t vote_results = calculate_district(districts[i], number_of_districts);
        print_district(districts[i], vote_results);

    }




  return 0;
}