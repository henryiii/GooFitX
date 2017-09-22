#include <goofit/FitManager.hpp>

#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_FCN(py::module &m) {
    py::class_<FCN>(m, "FCN")
    .def(py::init<Registry>())
    .def("__call__", &FCN::calculate_nll)
    .def("calculate_nnl", &FCN::calculate_nll)
    .def("get_params", &FCN::get_params)
    .def_property_readonly("params", &FCN::get_params)
    ;
}
