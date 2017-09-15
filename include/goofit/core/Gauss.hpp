#pragma once

#include <vector>
#include <cmath>

#include "Global.hpp"
#include "PDF.hpp"

namespace GooFit {
namespace experimental {

void gauss_fcn(fptype &out, const fptype &x, fptype mu, fptype sigma) {
    out = 1/sqrt(2*M_PI*sigma*sigma) * exp(-(x-mu)*(x-mu)/(2*sigma*sigma));
}

class Gauss : public PDF {
    InputRegistry x;
    InputVariable mu;
    InputVariable sigma;
    OutputRegistry result {this};

public:
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

}
}
