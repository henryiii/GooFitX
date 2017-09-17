#pragma once

//[py::name] Gauss
//[py::header] pybind11/numpy.h

#include <vector>
#include <cmath>

#include "Global.hpp"
#include "PDF.hpp"

namespace GooFit {
namespace experimental {
//[py] using namespace GooFit::experimental;

//[py] m.def("gauss_fcn", py::vectorize([](fptype x, fptype mu, fptype sigma){
//[py] fptype out; gauss_fcn(out, x, mu, sigma); return out;}),
//[py] "The gaussian function");
    
void gauss_fcn(fptype &out, const fptype &x, fptype mu, fptype sigma) {
    out = 1/sqrt(2*M_PI*sigma*sigma) * exp(-(x-mu)*(x-mu)/(2*sigma*sigma));
}

//[py] py::class_<Gauss>(m, "Gauss")
    
class Gauss : public PDF {
    InputRegistry x;
    InputVariable mu;
    InputVariable sigma;
    OutputRegistry result {this};

public:
    //[py] .def(py::init<Registry&, Variable&, Variable&>(
    //[py]    py::keep_alive<1,2>(), py::keep_alive<1,3>(), py::keep_alive<1,4>() )
    Gauss(Registry& x, Variable& mu, Variable& sigma)
        : PDF(), x(this, &x), mu(this, &mu), sigma(this, &sigma) {}

    std::vector<Registry*> output() {return outputs;}

    void calculate() override {
        // Call parent calculate, which calculates sources
        PDF::calculate();

        if(!current) {
            for(size_t i=0; i<x->size(); i++)
                gauss_fcn(result->at(i), x->at(i), mu, sigma);
            current = true;
        }
    }
};
    
//[py] ;
    
}
}
