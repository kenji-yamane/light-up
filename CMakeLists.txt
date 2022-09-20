cmake_minimum_required(VERSION 3.23)

project(light_up_agent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals -fPIC -Wall -march=native -g -fsanitize=address")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(src)
add_subdirectory(tst)

