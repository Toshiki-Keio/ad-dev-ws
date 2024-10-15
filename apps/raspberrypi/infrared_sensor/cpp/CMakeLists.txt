cmake_minimum_required(VERSION 3.22)
project(infrared_sensor)

# C++の標準バージョンを設定（必要に応じて変更）
set(CMAKE_CXX_STANDARD 14)


add_executable(${PROJECT_NAME} src/infrared_sensor.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/linux)
target_link_directories(${PROJECT_NAME} PRIVATE /usr/lib/linux)
target_link_libraries(${PROJECT_NAME} serial)