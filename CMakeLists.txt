cmake_minimum_required(VERSION 3.9)

project(GooFit3 LANGUAGES CXX)

add_library(goofit INTERFACE)
target_include_directories(goofit INTERFACE include)
target_compile_features(goofit INTERFACE cxx_std_14)

file(GLOB HEADERS "include/goofit/core/*.hpp")
add_executable(simple examples/simple.cpp ${HEADERS})
target_link_libraries(simple PUBLIC goofit)


