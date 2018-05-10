#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <goofit/Int.hpp>

#include "../pyhelpers.hpp"

namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Int(py::module &m) {
    
    py::class_<Int>(m, "Int")
        .def(py::init<int>())
        .def_property_readonly("value", &Int::get_value)
    
        .def(py::self == py::self)
        .def(py::self < py::self)
    
        .def("__repr__", &Int::__repr__)
        .def("__str__", &ostream_to_str<Int>)
    ;

}
