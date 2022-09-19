cmake_minimum_required(VERSION 3.23)

project(agent)

file(GLOB MODELING_SRCS modeling/*.cpp)
add_library(modeling ${MODELING_SRCS})

file(GLOB DECISION_MAKING_SRCS decision_making/*.cpp)
add_library(decision_making ${DECISION_MAKING_SRCS})

add_executable(first first.cpp)
target_link_libraries(first modeling decision_making)

add_executable(second second.cpp)
target_link_libraries(second modeling decision_making)

target_include_directories(modeling PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(decision_making PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})