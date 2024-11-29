#include <stdio.h>
#include <stdlib.h>
#include <header.h>

// Numbers are from 2022 currently (wikipedia)

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

void calculate_totals_and_seats(district_t districts[], int number_of_districts, int *dem_seats,
    int *rep_seats, int *other_seats, int *total_dem_votes, int *total_rep_votes, int *total_other_votes, int *total_votes);

void calculate_total_percentages(vote_percentage_t *total_vote_percentage, vote_percentage_t *seat_percentage,
    int total_votes,int dem_votes, int rep_votes, int other_votes, int dem_seats, int rep_seats, int other_seats, int number_of_districts);

void print_total_results(vote_percentage_t total_vote_percentage, vote_percentage_t seat_percentage, int dem_seats, int rep_seats, int other_seats, int total_votes);

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

void calculate_totals_and_seats(district_t districts[], int number_of_districts, int *dem_seats,
    int *rep_seats, int *other_seats, int *total_dem_votes, int *total_rep_votes, int *total_other_votes, int *total_votes) {
    *dem_seats = 0;
    *rep_seats = 0;
    *other_seats = 0;
    *total_votes = 0;
    *total_dem_votes = 0;
    *total_rep_votes = 0;
    *total_other_votes = 0;

    for (int i = 0; i < number_of_districts; i++) {
        *total_dem_votes += districts[i].dem_votes;
        *total_rep_votes += districts[i].rep_votes;
        *total_other_votes += districts[i].other_votes;
        *total_votes += districts[i].total_district_votes;

        if (districts[i].dem_votes > districts[i].rep_votes &&
            districts[i].dem_votes > districts[i].other_votes) {
            (*dem_seats)++;
        } else if (districts[i].rep_votes > districts[i].dem_votes &&
                    districts[i].rep_votes > districts[i].other_votes) {
            (*rep_seats)++;
        } else {
            (*other_seats)++;
        }
    }
}

void calculate_total_percentages(vote_percentage_t *total_vote_percentage, vote_percentage_t *seat_percentage, int total_votes,
    int dem_votes, int rep_votes, int other_votes, int dem_seats, int rep_seats, int other_seats, int number_of_districts) {
    // Calculate the total vote percentages
    total_vote_percentage -> dem_vote_percentage = 100.0 * dem_votes / total_votes;
    total_vote_percentage -> rep_vote_percentage = 100.0 * rep_votes / total_votes;
    total_vote_percentage -> other_vote_percentage = 100.0 * other_votes / total_votes;

    // Calculate the seat percentage
    seat_percentage->dem_vote_percentage = 100.0 * dem_seats / number_of_districts;
    seat_percentage->rep_vote_percentage = 100.0 * rep_seats / number_of_districts;
    seat_percentage->other_vote_percentage = 100.0 * other_seats / number_of_districts;
}

void print_total_results(vote_percentage_t total_vote_percentage, vote_percentage_t seat_percentage, int dem_seats, int rep_seats, int other_seats, int total_votes) {
    printf("Total results:\n");
    printf("Democratic seats: %d\n", dem_seats);
    printf("Republican Seats: %d\n", rep_seats);
    printf("Other Seats: %d\n", other_seats);
    printf("\n");

    printf("Percentage of seats:\n");
    printf("Democratic seat percentage: %lf\n", seat_percentage.dem_vote_percentage);
    printf("Republican Seat Percentage: %lf\n", seat_percentage.rep_vote_percentage);
    printf("Other Seat Percentage: %lf\n", seat_percentage.other_vote_percentage);
    printf("\n");

    printf("Total vote percentages:\n");
    printf("Democratic Vote Percentage: %lf\n", total_vote_percentage.dem_vote_percentage);
    printf("Republican Vote Percentage: %lf\n", total_vote_percentage.rep_vote_percentage);
    printf("Other Vote Percentage: %lf\n", total_vote_percentage.other_vote_percentage);
    printf("\n");
}

int main(void) {
    // Numbers are from 2022 currently (wikipedia)
    // Implement: Show what a proportional result of seats would be.
    // Implement: Ask the user for what they want to research (votes, percentages, seats, districts etc.)


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

    //Calculate and print all the districts
    for (int i = 0; i < number_of_districts; i++) {
        vote_percentage_t vote_results = calculate_percentages(districts[i]);
        print_district_votes(districts[i]);
        print_district_vote_percentages(vote_results);
    }

    int dem_seats, rep_seats, other_seats, total_dem_votes, total_rep_votes, total_other_votes, total_votes;
    vote_percentage_t total_vote_percentages, seat_percentages;

    // Calculate seats and total votes
    calculate_totals_and_seats(districts, number_of_districts, &dem_seats, &rep_seats, &other_seats, &total_dem_votes, &total_rep_votes, &total_other_votes, &total_votes);

    // Calculate percentages
    calculate_total_percentages(&total_vote_percentages, &seat_percentages, total_votes, total_dem_votes, total_rep_votes, total_other_votes,
        dem_seats, rep_seats, other_seats, number_of_districts);

    // Print results
    print_total_results(total_vote_percentages, seat_percentages, dem_seats, rep_seats, other_seats, total_votes);

  return 0;
}

