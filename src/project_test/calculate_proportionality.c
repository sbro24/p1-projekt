#include <stdio.h>
#include <stdlib.h>
#include <header.h>
#include <string.h>

#define TOTAL_VOTES 5217905;
#define DEM_TOTAL_VOTES 2328248;
#define REP_TOTAL_VOTES 2889657;
#define OTHER_TOTAL_VOTES 0;
#define TOTAL_SEATS 14

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

int calculate_proportionality(district_t district, int party_seats) {
    // Input the values from district
    char *name = district.district_number;
    double total_votes = district.total_votes;
    double dem_votes = district.dem_votes;
    double rep_votes = district.rep_votes;
    double other_votes = district.other_votes;

    // Calculate the voting percentages
    vote_percentage_t vote_percentage;
    for (int i = 0; i <= TOTAL_SEATS; i++) {
        vote_percentage.dem_vote_percentage = 100 * dem_votes / TOTAL_VOTES;
        vote_percentage.rep_vote_percentage = 100 * rep_votes / TOTAL_VOTES;
        vote_percentage.other_vote_percentage = 100 * other_votes / TOTAL_VOTES;
    }


}

void print_proportionality(district_t district) {
    // Input the values from district

    printf("%d:\n", district.district_number);
    printf("District total votes: %d\n", district.total_votes);
    printf("District votes for democrats: %d\n", district.dem_votes);
    printf("District votes for republicans: %d\n",district.rep_votes);
    printf("District votes for other parties: %d\n'", district.other_votes);
    printf("\n");

    printf("");

}
int main(void) {
    district_t districts[2] = {
        {1, 354523, 214596, 139927, 0},
        {2, 314054,140651, 173403, 0}
    };

    for (int i = 0; i < strlen(districts); i++) {
        print_proportionality(districts[i]);
    }




  return 0;
}