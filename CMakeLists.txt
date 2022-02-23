cmake_minimum_required(VERSION 3.21)
project(FoxString C)
project(FoxStringTest C)

project(FoxStringTestCpp CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_library(FoxString STATIC library.c library.h library.cpp)
set(LIBRARY_OUTPUT_PATH "../lib/")
set_target_properties(FoxString PROPERTIES PREFIX "")

find_library(FoxStringTest FoxString lib)
find_library(FoxStringTestCpp FoxString lib)
add_executable(FoxStringTest main.c)
add_executable(FoxStringTestCpp main.cpp)

target_link_libraries(FoxStringTest LINK_PUBLIC FoxString)
set_target_properties(FoxStringTest PROPERTIES OUTPUT_NAME "TestC")
target_link_libraries(FoxStringTestCpp LINK_PUBLIC FoxString)
set_target_properties(FoxStringTestCpp PROPERTIES OUTPUT_NAME "TestCPP")
set(EXECUTABLE_OUTPUT_PATH  "../")
