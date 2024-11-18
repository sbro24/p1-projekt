# We create an executable to run the program
add_library(lib
        input/test.c)

# Make header files in the current folder available for #include
target_include_directories(lib PUBLIC .)

# We create an executable to run the game
add_executable(p1_projekt main.c)

# We link our library to the program executable, so the executable can access the functions in the library.
target_link_libraries(p1_projekt lib)



