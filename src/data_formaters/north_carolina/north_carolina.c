#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct votes_t {
        int election_day;
        int early_voting;
        int absentee_by_mail;
        int provisional;
        int total;
    };
    typedef struct votes_t votes_t;

    struct raw_line_t {
        char county[30];
        char contest_name[60];
        char party[3];
        votes_t votes_t;
    };
    typedef struct raw_line_t raw_line_t;

    FILE *raw_file = fopen("north_carolina_raw_results_2024.txt", "r");
    if (raw_file == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    raw_line_t first_line;
    //skip first line
    fscanf(raw_file, "%*[^\n]\n");
    fscanf(raw_file, "%s \t %*s \t %*s \t %*s \t %*s \t %[^\t]s", &first_line.county, &first_line.contest_name);


    printf("%s \t %s\t %s", first_line.county, first_line.contest_name);
    return 0;
}
