cmake_minimum_required( VERSION 3.4.0 )
project (libs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread -fprofile-arcs -ftest-coverage")

add_subdirectory(static)
add_subdirectory(shared)

add_executable(${PROJECT_NAME} static/common_find.c shared/parallel_find.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )

target_link_libraries(
        ${PROJECT_NAME}
        pthread
)