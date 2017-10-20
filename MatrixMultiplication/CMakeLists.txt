cmake_minimum_required(VERSION 3.5)
project(matMultp)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c file_processing.h Matrix.h file_processing.c Thread_Data.h matrix_multiplication.h matrix_multiplication.c)
add_executable(matMultp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} pthread)
