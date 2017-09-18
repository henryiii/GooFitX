// Automatically generated from "goofit/core/Variable.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/Variable.hpp>
#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Variable(py::module &m) {
    py::class_<Variable>(m, "Variable")
    .def_readwrite("name", &Variable::name)
    .def_readwrite("value", &Variable::value)
    .def_readwrite("const", &Variable::const_)
    .def_readwrite("error", &Variable::error)
    .def_readwrite("min", &Variable::min_)
    .def_readwrite("max", &Variable::max_)
    .def(py::init<std::string, fptype>())
    ;

}
