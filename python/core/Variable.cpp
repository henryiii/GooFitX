// Automatically generated from "goofit/core/Variable.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/Variable.hpp>
#include <pybind11/pybind11.h>
#include "../pyhelpers.hpp"


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Variable(py::module &m) {
    py::class_<Variable>(m, "Variable")
    .def_property_readonly("name", &Variable::get_name)
    .def_property("value", &Variable::get_value, &Variable::set_value)
    .def_property("const", &Variable::get_const, &Variable::set_const)
    .def_property("error", &Variable::get_error, &Variable::set_error)
    .def_property("min", &Variable::get_min, &Variable::set_min)
    .def_property("max", &Variable::get_max, &Variable::set_max)
    .def(py::init<std::string, fptype>(), "Constant signature")
    .def(py::init<std::string, fptype, fptype, fptype, fptype>(), "Non-constant signature")
    .def("__repr__", &Variable::__repr__)
    .def("__str__", &ostream_to_str<Variable>)
    ;

}
