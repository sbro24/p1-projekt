#include <stdio.h>

#include "construct_state_header.h"
#include "header.h"


state_t construct_state(void) {
    state_t state;

    construct_counties();

    printf("Fucking construct_state AAAAAAAAAAAaAAAAAAAAAAAAAAA!\n");
    return state;
}
