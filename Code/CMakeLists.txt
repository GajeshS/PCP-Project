cmake_minimum_required(VERSION 3.10)
project(WSDEQueue)

file(GLOB_RECURSE PUBLIC_HEADERS ${PROJECT_SOURCE_DIR}/include/ *.hpp)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/  *.cpp)

add_library(WSDEQueue STATIC 
    ${PUBLIC_HEADERS}
    ${SRC}
)
target_include_directories(WSDEQueue PRIVATE  ${PROJECT_SOURCE_DIR}/include/)

add_executable(OUTPUT test/executable/test_program.cpp)
target_link_libraries(OUTPUT PRIVATE WSDEQueue)
target_include_directories(OUTPUT PRIVATE  ${PROJECT_SOURCE_DIR}/include/)
