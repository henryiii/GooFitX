#pragma once

#include <vector>
#include <cmath>
#include <pstl/algorithm>
#include <pstl/iterators.h>

#include "../../Global.hpp"
#include "../PDF.hpp"
#include "../../Log.hpp"


namespace GooFit {
namespace experimental {

// Must be: output (input, variables, ints)
fptype gauss_fcn(const fptype &x, fptype mu, fptype sigma) {
    return 1/sqrt(2*M_PI*sigma*sigma) * exp(-(x-mu)*(x-mu)/(2*sigma*sigma));
}
    
class Gauss : public PDF {
    InputRegistry x;
    InputVariable mu;
    InputVariable sigma;
    OutputRegistry result {this};

public:
    Gauss(Registry x, Variable mu, Variable sigma)
    : PDF("Gauss"), x(this, x), mu(this, mu), sigma(this, sigma) {}

    void calculate() override {
        // Call parent calculate, which calculates sources
        PDF::calculate();
        GOOFIT_DEBUG("Computing: {} {}", mu.value.get_value(), sigma.value.get_value());
        
        if(get_changed()) {
            fptype mu_ = mu.value.get_value();
            fptype sigma_ = sigma.value.get_value();
            
            std::transform(
                std::execution::par_unseq,
                x->begin(),
                x->end(),
                result->begin(),
                [mu_, sigma_](const fptype &x){
                    return gauss_fcn(x, mu_, sigma_);
                });
        }
    }
};
    

}
}
