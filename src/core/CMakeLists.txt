project(core_lib)

add_subdirectory(test)

add_library(core STATIC math_util.c util.c lottery.c)
target_include_directories(core PUBLIC include)
