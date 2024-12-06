# Unit test: Data import
add_executable(dataimport_test project_test/dataimport_test.c)
target_link_libraries(dataimport_test dataimporter_lib construct_state_lib)

# Unit test: Calculate Proportionality
add_executable(Calculate_proportionality lib/calculate_proportionality/calculate_proportionality.c)
target_link_libraries(calculate_proportionality_lib)


