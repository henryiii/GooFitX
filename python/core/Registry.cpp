#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <goofit/Registry.hpp>
#include <goofit/PDFs/PDF.hpp>

namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Registry(py::module &m) {

    py::class_<Registry>(m, "Registry")
        .def(py::init<size_t>(), "n"_a)
    
        .def("calcluate", &Registry::calculate, "Internal (mostly) update all")
        .def("get_source", &Registry::get_source)
        .def_property_readonly("source", &Registry::get_source)
    
        .def("get_variables_recursive", &Registry::get_variables_recursive)
        .def("get_pdfs_recursive", &Registry::get_pdfs_recursive)

        .def(py::self == py::self)
        .def(py::self < py::self)
        .def("__len__", [](Registry &r){return r.size();})
    ;
    
}
