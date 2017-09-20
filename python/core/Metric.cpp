// Automatically generated from "goofit/core/Metric.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/Metric.hpp>
#include <goofit/core/Registry.hpp>
#include <goofit/core/PDF.hpp>

#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Metric(py::module &m) {
     py::class_<Metric>(m, "Metric")
    .def(py::init<Registry>())
    .def(py::init<PDF&>())
    .def("get_input", &Metric::get_input)
    .def_property_readonly("input", &Metric::get_input)
    ;
}

void init_NLL(py::module &m) {
    py::class_<NLL, Metric>(m, "NLL")
    .def(py::init<Registry>())
    .def(py::init<PDF&>())
    .def("calculate", &NLL::calculate, "Bring all PDFs up to date and return NNL")
    ;

}
