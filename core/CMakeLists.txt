add_library(
    core 
    ./tokenizer.cpp
    )
target_link_libraries(core PUBLIC fmt)
target_include_directories(core PUBLIC ./include)
