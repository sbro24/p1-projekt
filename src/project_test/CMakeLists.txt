add_library(test_lib
        eval_map_test.c
        test.h
        dataimport_test.c
        Gallagher_index_test_2.c
        output_to_txt1.c
        construct_parties_test1.c)

target_link_libraries(test_lib
        calculate_proportionality_lib
        construct_state_lib
        dataimporter_lib
        eval_map_lib
        output_lib
)
