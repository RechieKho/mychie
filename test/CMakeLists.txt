add_executable(
    test 
    ./test.hpp 
    ./test.cpp
    )
target_link_libraries(test PRIVATE core)
