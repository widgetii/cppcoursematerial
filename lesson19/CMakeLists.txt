cmake_minimum_required(VERSION 3.5)
project(19_boost_2)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(fusion fusion.cpp)
add_executable(factory factory.cpp)
add_executable(signals2 signals2.cpp)
