#include <stdio.h>
#include <stdlib.h>
#include <header.h>

// Numbers are from 2022 currently (wikipedia)

#define TOTAL_VOTES 5217905;
#define DEM_TOTAL_VOTES 2328248;
#define REP_TOTAL_VOTES 2889657;
#define OTHER_TOTAL_VOTES 0;

//Structs
typedef struct  {
    int district_number;
    int total_district_votes;
    int dem_votes;
    int rep_votes;
    int other_votes;
} district_t;

typedef struct {
    double dem_vote_percentage;
    double rep_vote_percentage;
    double other_vote_percentage;
} vote_percentage_t;

// Function prototypes
vote_percentage_t calculate_percentages(district_t district);

void print_district_votes(district_t district);

void print_district_vote_percentages(vote_percentage_t vote_percentage);

// Functions
vote_percentage_t calculate_percentages(district_t district) {
    vote_percentage_t vote_percentage;

    // Calculate the voting percentages
    vote_percentage.dem_vote_percentage = 100.0 * district.dem_votes / district.total_district_votes;
    vote_percentage.rep_vote_percentage = 100.0 * district.rep_votes / district.total_district_votes;
    vote_percentage.other_vote_percentage = 100.0 * district.other_votes / district.total_district_votes;

    return vote_percentage;
}

void print_district_votes(district_t district) {
    // Input the values from district

    printf("District %d:\n", district.district_number);
    printf("District total votes: %d\n", district.total_district_votes);
    printf("District votes for democrats: %d\n", district.dem_votes);
    printf("District votes for republicans: %d\n",district.rep_votes);
    printf("District votes for other parties: %d\n", district.other_votes);
    printf("\n");

}

void print_district_vote_percentages(vote_percentage_t vote_percentage) {

    printf("Democratic Vote Percentage: %lf\n", vote_percentage.dem_vote_percentage);
    printf("Republican Vote Percentage: %lf\n", vote_percentage.rep_vote_percentage);
    printf("Other Vote Percentage: %lf\n", vote_percentage.other_vote_percentage);
    printf("\n");
}

int main(void) {
    // Numbers are from 2022 currently (wikipedia)

    district_t districts[] = {
        {1, 257776, 134996, 122780, 0},
        {2, 294869, 190714, 104155, 0},
        {3, 248898, 82378, 166520, 0},
        {4, 291425, 194983, 96442, 0},
        {5, 277548, 102269, 175279, 0},
        {6, 258998, 139553, 116635, 2810},
        {7, 284269, 120222, 164047, 0},
        {8, 263190, 79192, 183998, 0},
        {9, 232655, 101202, 131453, 0},
        {10, 268207, 73174, 194681, 0},
        {11, 323912,144165, 174232, 5515},
        {12, 223908,140494, 83414, 0},
        {13, 277346,143090, 134256, 0},
        {14, 257752,148738, 109014, 0}
    };
    int number_of_districts = sizeof(districts) / sizeof(districts[0]);

    for (int i = 0; i < number_of_districts; i++) {
        vote_percentage_t vote_results = calculate_percentages(districts[i]);
        print_district_votes(districts[i]);
        print_district_vote_percentages(vote_results);

    }




  return 0;
}

