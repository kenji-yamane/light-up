cmake_minimum_required(VERSION 3.23)

project(agent)

file(GLOB SRCS modeling/*.cpp)

add_library(modeling ${SRCS})

add_executable(agent main.cpp)

target_link_libraries(agent modeling)

target_include_directories(modeling PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})