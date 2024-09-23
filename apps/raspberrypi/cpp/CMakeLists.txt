cmake_minimum_required(VERSION 3.5)
project(infrared_sensor)

find_package(Serial REQUIRED)

add_executable(${PROJECT_NAME}
               src/main.cpp)
target_link_libraries(${PROJECT_NAME} Serial::Serial)

