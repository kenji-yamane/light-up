cmake_minimum_required(VERSION 3.23)

project(testing)

add_executable(test-main main.cpp)
target_link_libraries(test-main modeling decision_making parser)
