cmake_minimum_required(VERSION 3.17)

project(fourierdrawer)

find_package(SFML REQUIRED graphics)

add_executable(fourierdrawer src/main.cpp)

target_link_libraries(fourierdrawer sfml-graphics m)
