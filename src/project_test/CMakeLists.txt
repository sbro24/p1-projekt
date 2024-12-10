add_library(test_lib
        eval_map_test.c
        test.h
        dataimport_test.c
        gallagher_index_test.c)

target_link_libraries(test_lib
        calculate_proportionality_lib
        construct_state_lib
        dataimporter_lib
        eval_map_lib
)
