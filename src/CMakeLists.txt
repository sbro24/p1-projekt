
# add src directory
include_directories(${CMAKE_SOURCE_DIR}/src)
# add library directory
add_subdirectory(lib)
add_subdirectory(project_test)
# Make header files in the current folder available for #include
target_include_directories(calculate_proportionality_lib PUBLIC lib/calculate_proportionality)
target_include_directories(construct_state_lib PUBLIC lib/construct_state)
target_include_directories(dataimporter_lib PUBLIC lib/DataImporter)
target_include_directories(eval_map_lib PUBLIC lib/eval_map)
target_include_directories(test_lib PUBLIC lib/test)

# Main executable
add_executable(p1_projekt main.c
        header.h)

# Main library link
target_link_libraries(p1_projekt
        calculate_proportionality_lib
        construct_state_lib
        dataimporter_lib
        eval_map_lib
        test_lib
)


