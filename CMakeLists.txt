cmake_minimum_required(VERSION 3.1)
project(birdpocalypse)

set(CMAKE_CXX_STANDARD 20)

add_executable(birdpocalypse main.cpp)

find_package(SFML 2 REQUIRED graphics)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)


if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(birdpocalypse sfml-graphics)
endif()

if(Eigen3_FOUND)
    target_link_libraries(birdpocalypse Eigen3::Eigen)
endif()

