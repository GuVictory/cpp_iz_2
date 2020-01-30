project(shared_lib)

set(CMAKE_CXX_FLAGS "-pthread -fprofile-arcs -ftest-coverage")

add_library(${PROJECT_NAME} SHARED parallel_find.c)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        )


add_dependencies(${PROJECT_NAME} sub::lib2)

target_link_libraries(
        ${PROJECT_NAME}
        sub::lib2
        pthread
)



