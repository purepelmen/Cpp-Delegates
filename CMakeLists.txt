cmake_minimum_required(VERSION 3.0)

project(Delegates-Test)
add_executable(Delegates-Test test-src/main.cpp)
target_include_directories(Delegates-Test PUBLIC include)
