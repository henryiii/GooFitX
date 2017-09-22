cmake_minimum_required(VERSION 3.9)

project(GooFitX LANGUAGES CXX VERSION 0.1)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

add_subdirectory(extern/pybind11)
add_subdirectory(extern/Minuit2)

set_target_properties(Minuit2 PROPERTIES CXX_VISIBILITY_PRESET hidden)

add_library(goofit INTERFACE)
target_include_directories(goofit INTERFACE include)
target_compile_features(goofit INTERFACE cxx_std_14)
target_link_libraries(goofit INTERFACE Minuit2)

file(GLOB CORE_HEADERS "include/goofit/core/*.hpp")
add_executable(simple examples/simple.cpp ${CORE_HEADERS})
target_link_libraries(simple PUBLIC goofit)

file(GLOB CORE_PYTHON "python/core/*.cpp")
pybind11_add_module(goofitx python/goofit.cpp python/pyhelpers.hpp ${CORE_PYTHON} ${CORE_HEADERS})
target_link_libraries(goofitx PUBLIC goofit)
