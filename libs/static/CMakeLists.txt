project(static_lib)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
add_library(${PROJECT_NAME} common_find.c)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        )