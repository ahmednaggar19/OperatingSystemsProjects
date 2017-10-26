cmake_minimum_required(VERSION 3.8)
project(TrainStation)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES caltrain.h caltrain.c caltrain-runner.c)
add_executable(TrainStation ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} pthread)