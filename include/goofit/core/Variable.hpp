#pragma once

#include <vector>
#include <string>

#include "Global.hpp"

//[py::name] Varaible
//[py::header] pybind11/numpy.h
//[py] using namespace GooFit::experimental;


namespace GooFit {
namespace experimental {

    
//[py] py::class_<Variable>(m, "Variable")
struct Variable {
    //[py] .def_readwrite("name", &Variable::name)
    std::string name;
    
    //[py] .def_readwrite("value", &Variable::value)
    fptype value;
    
    //[py] .def_readwrite("const", &Variable::const_)
    bool const_;
    
    //[py] .def_readwrite("error", &Variable::error)
    fptype error {0};
    
    //[py] .def_readwrite("min", &Variable::min_)
    fptype min_ {0};
    
    //[py] .def_readwrite("max", &Variable::max_)
    fptype max_ {0};

public:
    //[py] .def(py::init<std::string, fptype>())
    /// New Variable
    Variable(std::string name, fptype value) : name(name), value(value), const_(true) {}

    /// Can't copy
    Variable(Variable&) = delete;

    //[py] ;
};

}
}
