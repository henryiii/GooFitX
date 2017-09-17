#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

#include "Global.hpp"
#include "PDF.hpp"

//[py::name] Metric


//[py] using namespace GooFit::experimental;
namespace GooFit {
namespace experimental {

class Registry;

    
//[py] py::class_<Metric>(m, "Metric")
class Metric {
protected:
    Registry* input;

public:
    //[py] .def(py::init<Registry*>())
    Metric(Registry* input) : input(input) {}
    
    //[py] .def(py::init<PDF&>())
    Metric(PDF &input) : input(input.output()) {}
    
    Metric(Metric&) = delete;
    
//[py] ;
};
    
//[py] py::class_<NLL, Metric>(m, "NLL")
class NLL : public Metric {

public:
    using Metric::Metric;

    //[py] .def("calculate", &NLL::calculate, "Bring all PDFs up to date and return NNL")
    double calculate() {
        input->calculate();
        std::vector<double> outs(input->size());
        std::transform(input->begin(), input->end(), outs.begin(), [](fptype v){return -log(static_cast<double>(v));});
        return std::accumulate(outs.begin(), outs.end(), 0, std::plus<double>());
    }
//[py] ;
};

}
}
