cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(SLAM)
find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(cppzmq)

file(GLOB source_files
        "*.h"
        "Headers/*"
        "Source/*"
        "*.cpp"
        "config/*"
        )

set(SOURCE_FILES main.cpp)
add_executable(pcl ${source_files})
target_link_libraries(pcl ${PCL_LIBRARIES} cppzmq)


SET(COMPILE_FLAGS "-std=c++11")
add_definitions(${COMPILE_FLAGS})
