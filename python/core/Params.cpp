#include <goofit/core/FitManager.hpp>

#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Params(py::module &m) {
    py::class_<Params>(m)
    .def("__len__", &Params::size)
    ;
}
