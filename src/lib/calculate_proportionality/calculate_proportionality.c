#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//Structs

typedef struct  {
    int district_number;
    int dem_votes;
    int rep_votes;
    int other_votes;
    int total_votes;
} district_t;

typedef struct {
    double dem_vote_percentage;
    double rep_vote_percentage;
    double other_vote_percentage;
} vote_percentage_t;

typedef struct {
    int total_dem_votes;
    int total_rep_votes;
    int total_other_votes;
    int total_state_votes;
} total_votes_t;

typedef struct {
    int dem_seats;
    int rep_seats;
    int other_seats;
} seats_t;

typedef struct {
    double total_dem_vote_percentage;
    double total_rep_vote_percentage;
    double total_other_vote_percentage;
    double dem_seat_percentage;
    double rep_seat_percentage;
    double other_seat_percentage;
} total_percentages_t;

typedef struct {
    double dem_difference_squared;
    double rep_difference_squared;
    double other_difference_squared;
    double half_of_sum_of_difference_squared;
    double gallagher_index;
} gallagher_index_t;

// Function prototypes

district_t calculate_total_district_votes(district_t district);

vote_percentage_t calculate_district_vote_percentages(district_t district);

void print_district_votes(district_t district);

void print_district_vote_percentages(vote_percentage_t vote_percentage);

total_votes_t calculate_total_votes(district_t districts[], int number_of_districts);

seats_t calculate_seats(district_t districts[], int number_of_districts);

total_percentages_t calculate_total_percentages(seats_t seats, total_votes_t total_votes, int number_of_districts);

void print_total_results(total_percentages_t total_percentages, total_percentages_t seat_percentage, seats_t seats);

gallagher_index_t calculate_gallagher_index(total_percentages_t total_percentages);

void print_gallagher_index(gallagher_index_t gallagher_index);

void calculate_proportionality(void);

/*------------------------------------------------------------------------------------------------------------------*/
// Functions

district_t calculate_total_district_votes(district_t district) {

    district.total_votes = district.dem_votes + district.rep_votes + district.other_votes;

    return district;
}

vote_percentage_t calculate_district_vote_percentages(district_t district) {
    vote_percentage_t vote_percentage;

    // Calculate the voting percentages
    vote_percentage.dem_vote_percentage = 100.0 * district.dem_votes / district.total_votes;
    vote_percentage.rep_vote_percentage = 100.0 * district.rep_votes / district.total_votes;
    vote_percentage.other_vote_percentage = 100.0 * district.other_votes / district.total_votes;

    return vote_percentage;
}

void print_district_votes(district_t district) {
    // Input the values from district

    printf("District %d:\n", district.district_number);
    printf("District total votes: %d\n", district.total_votes);
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

total_votes_t calculate_total_votes(district_t districts[], int number_of_districts) {
    total_votes_t total_votes = {0};

    for (int i = 0; i < number_of_districts; i++) {
        total_votes.total_dem_votes += districts[i].dem_votes;
        total_votes.total_rep_votes += districts[i].rep_votes;
        total_votes.total_other_votes += districts[i].other_votes;
        total_votes.total_state_votes += districts[i].dem_votes + districts[i].rep_votes + districts[i].other_votes;
    }
    return total_votes;
}

seats_t calculate_seats(district_t districts[], int number_of_districts) {
    seats_t seats = {0};

    for (int i = 0; i < number_of_districts; i++) {
        if (districts[i].dem_votes > districts[i].rep_votes &&
                districts[i].dem_votes > districts[i].other_votes) {
        seats.dem_seats++;
        } else if (districts[i].rep_votes > districts[i].dem_votes &&
                    districts[i].rep_votes > districts[i].other_votes) {
        seats.rep_seats++;
        } else {
        seats.other_seats++;
        }
    }
    return seats;
}

total_percentages_t calculate_total_percentages(seats_t seats,total_votes_t total_votes, int number_of_districts) {
    total_percentages_t total_percentages = {0};
    // Calculate the total vote percentages
    total_percentages.total_dem_vote_percentage = 100.0 * total_votes.total_dem_votes / total_votes.total_state_votes;
    total_percentages.total_rep_vote_percentage = 100.0 * total_votes.total_rep_votes / total_votes.total_state_votes;
    total_percentages.total_other_vote_percentage = 100.0 * total_votes.total_other_votes / total_votes.total_state_votes;

    // Calculate the seat percentage
    total_percentages.dem_seat_percentage = 100.0 * seats.dem_seats / number_of_districts;
    total_percentages.rep_seat_percentage = 100.0 * seats.rep_seats / number_of_districts;
    total_percentages.other_seat_percentage = 100.0 * seats.other_seats / number_of_districts;

    return total_percentages;
}

void print_total_results(total_percentages_t total_percentages, total_percentages_t seat_percentage, seats_t seats) {
    printf("Total results:\n");
    printf("Democratic seats: %d\n", seats.dem_seats);
    printf("Republican Seats: %d\n", seats.rep_seats);
    printf("Other Seats: %d\n", seats.other_seats);
    printf("\n");

    printf("Percentage of seats:\n");
    printf("Democratic seat percentage: %lf\n", seat_percentage.dem_seat_percentage);
    printf("Republican Seat Percentage: %lf\n", seat_percentage.rep_seat_percentage);
    printf("Other Seat Percentage: %lf\n", seat_percentage.other_seat_percentage);
    printf("\n");

    printf("Total vote percentages:\n");
    printf("Democratic Vote Percentage: %lf\n", total_percentages.total_dem_vote_percentage);
    printf("Republican Vote Percentage: %lf\n", total_percentages.total_rep_vote_percentage);
    printf("Other Vote Percentage: %lf\n", total_percentages.total_other_vote_percentage);
    printf("\n");
}


gallagher_index_t calculate_gallagher_index(total_percentages_t percentages) {
    gallagher_index_t gallagher_index;

    // Calculate the difference in percentages of votes and seats, then squared
    gallagher_index.dem_difference_squared = pow((percentages.total_dem_vote_percentage - percentages.dem_seat_percentage),2);
    gallagher_index.rep_difference_squared = pow((percentages.total_rep_vote_percentage - percentages.rep_seat_percentage),2);
    gallagher_index.other_difference_squared = pow((percentages.total_other_vote_percentage - percentages.other_seat_percentage),2);

    // Calculate the sum of the difference squared
    gallagher_index.half_of_sum_of_difference_squared = (gallagher_index.dem_difference_squared +
                                                        gallagher_index.rep_difference_squared + gallagher_index.other_difference_squared) / 2;

    gallagher_index.gallagher_index = sqrt(gallagher_index.half_of_sum_of_difference_squared);

    return gallagher_index;
}

void print_gallagher_index(gallagher_index_t gallagher_index) {
    printf("Gallagher Index of North Carolina: %lf\n", gallagher_index.gallagher_index);
}

void calculate_proportionality(void) {
    // Numbers are from 2012 currently (wikipedia)
    // Implement: Show what a proportional result of seats would be.
    // Implement: Ask the user for what they want to research (votes, percentages, seats, districts etc.)
    char data, specific;

    // Boolean product to run or break the while loop
    // When true, it breaks out of the loop, therefore it starts as false
    bool valid_input = false;
    while (!valid_input) {
        printf("Do you want specific or all data? (specific = s, all = a)\n");
        scanf(" %c", &data);

        if (data == 'a' || data == 'A' ||
            data == 's' || data == 'S') {
            valid_input = true;
        } else {
            printf("Wrong input, try again)\n;");
        }
    }
    if (data == 's' || data == 'S') { // User picked a specific data
        bool valid_specific = false;
        while (!valid_specific) {
            printf("What data would you like?\n");
            printf("(District data = d)\n");
            printf("(Total results = t)\n");
            printf("(Gallagher index = i)\n");
            scanf(" %c", &specific);

            if (specific == 'd' || specific == 'D' ||
                specific == 't' || specific == 'T' ||
                specific == 'i' || specific == 'I') {
                valid_specific = true;
            } else {
                printf("Wrong input, try again)\n;");
            }
        }
    }

    district_t districts[] = {
        {1, 254644, 77288, 6134},
        {2, 128973, 174066, 8358},
        {3, 114314, 195571, 0},
        {4, 259534, 88951, 0},
        {5, 148252, 200945, 0},
        {6, 142467, 222116, 0},
        {7, 168695, 168041, 0},
        {8, 137139, 160695, 4446},
        {9, 171503, 194537, 9650},
        {10, 144023, 190826, 0},
        {11,141107, 190319, 5515},
        {12,247591, 63317, 0},
        {13,160115, 210495, 0},
    };
    int number_of_districts = sizeof(districts) / sizeof(districts[0]);

    // Calculate the universally needed data
        // Calculate total votes
        total_votes_t total_votes = calculate_total_votes(districts, number_of_districts);
        // Calculate seats
        seats_t seats = calculate_seats(districts, number_of_districts);
        // Calculate percentages of votes and seats
        total_percentages_t total_percentages = calculate_total_percentages(seats, total_votes, number_of_districts);


    if (data == 'a' || data == 'A') { // User wants all data
        for (int i = 0; i < number_of_districts; i++) {
            //Calculate and print all the districts
            districts[i] = calculate_total_district_votes(districts[i]);
            vote_percentage_t vote_results = calculate_district_vote_percentages(districts[i]);
            print_district_votes(districts[i]);
            print_district_vote_percentages(vote_results);

            print_total_results(total_percentages, total_percentages, seats);

            print_gallagher_index(calculate_gallagher_index(total_percentages));
        }
    } else if (specific == 'd' || specific == 'D' ) { // User wants specifically district data
        for (int i = 0; i < number_of_districts; i++) {
            //Calculate and print all the districts
            districts[i] = calculate_total_district_votes(districts[i]);
            vote_percentage_t vote_results = calculate_district_vote_percentages(districts[i]);
            print_district_votes(districts[i]);
            print_district_vote_percentages(vote_results);
        }
    } else if (specific == 't' || specific == 'T') { // User wants specifically the total results

        // Print results
        print_total_results(total_percentages, total_percentages, seats);
    } else if (specific == 'i' || specific == 'I') {
        // print gallagher index
        print_gallagher_index(calculate_gallagher_index(total_percentages));
    }
}

/*
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
        vote_percentage_t vote_results = calculate_district_vote_percentages(districts[i]);
        print_district_votes(districts[i]);
        print_district_vote_percentages(vote_results);
    }

    // Calculate total votes
    total_votes_t total_votes = calculate_total_votes(districts, number_of_districts);

    // Calculate seats
    seats_t seats = calculate_seats(districts, number_of_districts);

    // Calculate percentages of votes and seats
    total_percentages_t total_percentages = calculate_total_percentages(seats, total_votes, number_of_districts);

    // Print results
    print_total_results(total_percentages, total_percentages, seats);

    // print gallagher index
    print_gallagher_index(calculate_gallagher_index(total_percentages));
}
*/

int main(void) {

    calculate_proportionality();

  return 0;
}

