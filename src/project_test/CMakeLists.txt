# Unit test: Data import
add_executable(dataimport_test dataimport_test.c)
target_link_libraries(dataimport_test dataimporter_lib construct_state_lib)

# Unit test: Evaluate map
add_executable(eval_map_test eval_map_test.c)
target_link_libraries(eval_map_test eval_map_lib)



