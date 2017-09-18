// Automatically generated from "goofit/core/Metric.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/Metric.hpp>
#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;

void init_Metric(py::module &m) {
using namespace GooFit::experimental;
    py::class_<Metric>(m, "Metric")
    .def(py::init<Registry*>())
    .def(py::init<PDF&>())
    ;
    
    py::class_<NLL, Metric>(m, "NLL")
    .def("calculate", &NLL::calculate, "Bring all PDFs up to date and return NNL")
    ;

}
