#include <stdio.h>
#include <stdlib.h>
#include <header.h>

struct district_t {
    char name[20];
    int total_votes;
    int dem_votes;
    int rep_votes;
    int other_votes;
};

void calculate_proportionality(struct district_t, int total_seats, int party_seats) {
    struct district_t district_1 = {"District 1", 354523, 214596, 139927, 0};

    double dem_vote_percentage = (district_1.dem_votes / district_1.total_votes) * 100;
    double rep_vote_percentage = (district_1.rep_votes / district_1.total_votes) * 100;
    double other_vote_percentage = (district_1.other_votes / district_1.total_votes) * 100;

}
int main(void) {
    struct district_t district_1 = {"District 1", 354523, 214596, 139927, 0};



  return 0;
}