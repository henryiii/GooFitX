
#include <goofit/Variable.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "../pyhelpers.hpp"


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Variable(py::module &m) {
    py::class_<Variable>(m, "Variable")
        .def(py::init<std::string, double>(), "Constant signature",
             "name"_a, "value"_a)
        .def(py::init<std::string, double, double>(), "Free signature",
             "name"_a, "value"_a, "error"_a)
        .def(py::init<std::string, double, double, double, double, bool>(), "Non-constant (full) signature",
             "name"_a, "value"_a, "error"_a, "min"_a, "max"_a, "constant"_a = false)
        
        .def_property_readonly("name", &Variable::get_name)
        .def_property_readonly("index", &Variable::get_index)
        .def_property("value", &Variable::get_value, &Variable::set_value)
        .def_property("const", &Variable::get_const, &Variable::set_const)
        .def_property("error", &Variable::get_error, &Variable::set_error)
        .def_property("min", &Variable::get_min, &Variable::set_min)
        .def_property("max", &Variable::get_max, &Variable::set_max)
        .def_property("changed", &Variable::get_changed, &Variable::set_changed)
        .def_property("blind", &Variable::get_blind, &Variable::set_blind)
        
        .def(py::self == py::self)
        .def(py::self < py::self)
        
        .def("__repr__", &Variable::__repr__)
        .def("__str__", &ostream_to_str<Variable>)
    ;
}
