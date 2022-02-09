cmake_minimum_required(VERSION 3.16)

project(tee)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(
    tee
    ${tee_SOURCE_DIR}/src/Tee.cpp
    ${tee_SOURCE_DIR}/src/main.cpp
)


target_include_directories(
    tee
    PRIVATE
    ${tee_SOURCE_DIR}/include
)
