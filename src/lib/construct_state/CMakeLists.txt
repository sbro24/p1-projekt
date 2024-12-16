add_library(construct_state_lib
        construct_state_header.h
        construct_counties.c
        construct_state.c
        construct_parties.c
)

target_link_libraries(construct_state_lib
        dataimporter_lib
)