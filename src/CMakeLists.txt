# We create an executable to run the program
add_library(lib
        input/test.c
        construct_state/construct_state.c
        construct_state/construct_counties.c
        construct_state/construct_state_header.h
)

# Make header files in the current folder available for #include
target_include_directories(lib PUBLIC .)

# We create an executable to run the game
add_executable(p1_projekt main.c
        header.h)

# We link our library to the program executable, so the executable can access the functions in the library.
target_link_libraries(p1_projekt lib)

# Data formaters executables
add_executable(data_formater_north_carolina data_formaters/north_carolina/north_carolina.c)
# We link our library to the program executable, so the executable can access the functions in the library.
target_link_libraries(data_formater_north_carolina lib)

# Data formaters executables
add_executable(graph_test project_test/graph_test.c)
# We link our library to the program executable, so the executable can access the functions in the library.
target_link_libraries(graph_test lib)

# Data formaters executables
add_executable(proportionality_test project_test/calculate_proportionality.c)
# We link our library to the program executable, so the executable can access the functions in the library.
target_link_libraries(proportionality_test lib)

add_subdirectory(eval_map)