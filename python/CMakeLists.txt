
file(GLOB CORE_PYTHON "core/*.cpp")
pybind11_add_module(goofitx goofit.cpp pyhelpers.hpp ${CORE_PYTHON} ${CORE_HEADERS})
target_link_libraries(goofitx PUBLIC goofit)

