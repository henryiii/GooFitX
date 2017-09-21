cmake_minimum_required(VERSION 3.9)

project(GooFitX LANGUAGES CXX)

add_library(goofit INTERFACE)
target_include_directories(goofit INTERFACE include)
target_compile_features(goofit INTERFACE cxx_std_14)

file(GLOB CORE_HEADERS "include/goofit/core/*.hpp")
add_executable(simple examples/simple.cpp ${CORE_HEADERS})
target_link_libraries(simple PUBLIC goofit)

add_subdirectory(extern/pybind11)
add_subdirectory(extern/Minuit2)

file(GLOB CORE_PYTHON "python/core/*.cpp")
pybind11_add_module(goofitx python/goofit.cpp python/pyhelpers.hpp ${CORE_PYTHON} ${CORE_HEADERS})
target_link_libraries(goofitx PUBLIC goofit Minuit2)
