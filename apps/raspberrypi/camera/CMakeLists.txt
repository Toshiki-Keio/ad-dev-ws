cmake_minimum_required(VERSION 3.6)

project(libcamera-find)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_definitions(-D_FILE_OFFSET_BITS=64)


find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)

message(STATUS "libcamera library found:")
message(STATUS "    version: ${LIBCAMERA_VERSION}")
message(STATUS "    libraries: ${LIBCAMERA_LINK_LIBRARIES}")
message(STATUS "    include path: ${LIBCAMERA_INCLUDE_DIRS}")
include_directories(include ${LIBCAMERA_INCLUDE_DIRS})

set(TARGET cam_test)
add_executable(${TARGET} src/camera.cpp)
target_link_libraries(${TARGET} ${LIBCAMERA_LINK_LIBRARIES})