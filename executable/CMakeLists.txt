project(cpp_iz2)

# Create the executable
add_executable(${PROJECT_NAME} main.c)

# Link the static library from subproject1 using it's alias sub::lib1
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
        sub::lib1
        sub::lib2
        )