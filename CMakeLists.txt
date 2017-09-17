cmake_minimum_required(VERSION 3.9)

project(GooFitX LANGUAGES CXX)

add_library(goofit INTERFACE)
target_include_directories(goofit INTERFACE include)
target_compile_features(goofit INTERFACE cxx_std_14)

file(GLOB CORE_HEADERS "include/goofit/core/*.hpp")
add_executable(simple examples/simple.cpp ${CORE_HEADERS})
target_link_libraries(simple PUBLIC goofit)

add_subdirectory(extern/pybind11)

# Make binding files
foreach(header ${CORE_HEADERS})
    get_filename_component(LNAME "${header}"  NAME_WE)
    set(OUTNAME "${CMAKE_CURRENT_BINARY_DIR}/python/core/${LNAME}.cpp")
    list(APPEND CORE_PYTHON "${OUTNAME}")
    add_custom_command(
        OUTPUT "python/core/${LNAME}.cpp"
        COMMAND "${PYTHON_EXECUTABLE}"
                "${CMAKE_CURRENT_SOURCE_DIR}/scripts/make_binding.py"
                "${header}" "${OUTNAME}"
        DEPENDS "${header}" "${CMAKE_CURRENT_SOURCE_DIR}/scripts/make_binding.py")
endforeach()

pybind11_add_module(goofitx python/goofit.cpp ${CORE_PYTHON})
target_link_libraries(goofitx PUBLIC goofit)
