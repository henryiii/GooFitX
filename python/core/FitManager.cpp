#include <goofit/core/FitManager.hpp>

#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_FitManager(py::module &m) {
    py::class_<FitManager>(m, "FitManager")
    .def(py::init<FCN&>())
    .def(py::init<Registry&>())
    .def(py::init<PDF&>())
    .def("get_fcn", &FitManager::get_fcn)
    .def("calculate_nll", &FitManager::calculate_nll)
    .def("fit", &FitManager::fit, "verbosity"_a = 3)
    ;
}
