cmake_minimum_required(VERSION 3.9)

project(GooFitX LANGUAGES CXX VERSION 0.1)

# Never, never do an in-source build!!!
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# Needed for Minuit and PyBind to be happy together
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Minuit2 copy
add_subdirectory(extern/Minuit2)
set_target_properties(Minuit2Math PROPERTIES FOLDER extern)
set_target_properties(Minuit2 PROPERTIES FOLDER extern)


# Color library
add_library(rang INTERFACE)
target_include_directories(rang INTERFACE extern/rang/include)


# FMT library
add_subdirectory("extern/fmt")
set_target_properties(fmt PROPERTIES FOLDER extern)
mark_as_advanced(FMT_CPPFORMAT FMT_DOC FMT_INSTALL FMT_PEDANTIC FMT_TEST FMT_USE_CPP11)


# Eigen
add_library(Eigen INTERFACE)
target_include_directories(Eigen INTERFACE "${PROJECT_SOURCE_DIR}/extern/Eigen")

# VexCL
add_subdirectory(extern/vexcl)

# Main library
add_library(goofit INTERFACE)
target_include_directories(goofit INTERFACE include)
target_compile_features(goofit INTERFACE cxx_std_14)
target_link_libraries(goofit INTERFACE Minuit2 rang fmt Eigen)
target_link_libraries(goofit INTERFACE VexCL::Common)
set(GOOFIT_HEADERS_ORIG
    Application.hpp
    Color.hpp
    FCN.hpp
    FitManager.hpp
    Global.hpp
    Int.hpp
    Log.hpp
    Params.hpp
    Registry.hpp
    RegistryNoInl.hpp
    Variable.hpp
    PDFs/PDF.hpp
    PDFs/simple/Gauss.hpp
)

foreach(f ${GOOFIT_HEADERS_ORIG})
    list(APPEND GOOFIT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/goofit/${f}")
endforeach()


# Examples
add_subdirectory(examples)


# Testing
add_subdirectory(extern/Catch2)
enable_testing()
add_subdirectory(tests)


# Python
add_subdirectory(extern/pybind11)
add_subdirectory(python)

