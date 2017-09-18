// Automatically generated from "goofit/core/RegistryNoInl.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/Registry.hpp>
#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Registry(py::module &m) {
    
    
    py::class_<Registry>(m, "Registry", py::buffer_protocol())
        .def(py::init<size_t>(), "n"_a)
        .def_buffer([](Registry &r) -> py::buffer_info {
            return py::buffer_info(
                               r.data(),                                /* Pointer to buffer */
                               sizeof(fptype),                          /* Size of one scalar */
                               py::format_descriptor<fptype>::format(), /* Python struct-style format descriptor */
                               1,                                      /* Number of dimensions */
                               { r.size() },                 /* Buffer dimensions */
                               { sizeof(float) }             /* Strides (in bytes) for each index */
                               );
           })
        .def("calcluate", &Registry::calculate, "Internal (mostly) update all")
    ;
    
}
