// Automatically generated from "goofit/core/PDF.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/PDF.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_PDF(py::module &m) {
using namespace GooFit::experimental;
py::class_<PDF>(m, "PDF")
    .def(py::init<>())
    .def("output", &PDF::output)
    .def("calculate", &PDF::calculate)
    .def("size", &PDF::size)
    .def("get_inputs", &PDF::get_inputs)
    .def("get_outputs", &PDF::get_outputs)
    .def("get_variables", &PDF::get_variables)
    .def_property_readonly("inputs", &PDF::get_inputs)
    .def_property_readonly("outputs", &PDF::get_outputs)
    .def_property_readonly("variables", &PDF::get_variables)
;

}
