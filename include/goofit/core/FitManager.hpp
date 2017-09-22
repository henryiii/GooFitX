#pragma once

#include "Global.hpp"

#include <memory>
#include <set>
#include <numeric>
#include <cmath>

#include "FCN.hpp"
#include "Params.hpp"

#include "Minuit2/MnPrint.h"
#include <Minuit2/FunctionMinimum.h>
#include <Minuit2/MnMigrad.h>
#include <Minuit2/MnUserParameterState.h>

namespace GooFit {
namespace experimental {

class FitManager {
    FCN fcn_;
    
public:
    FitManager(FCN &fcn) : fcn_(fcn) {}
    FitManager(Registry &reg) : fcn_(reg) {}
    FitManager(PDF &pdf) : fcn_(pdf.output()) {}
    
    FCN* get_fcn() {return &fcn_;}
    
    double calculate_nll() {
        return fcn_.calculate_nll();
    }
    
    Minuit2::FunctionMinimum fit(int verbosity=3) {
        auto val = Minuit2::MnPrint::Level();
        Minuit2::MnPrint::SetLevel(verbosity);
        
        Minuit2::MnMigrad migrad{fcn_, fcn_.get_params()};
        Minuit2::FunctionMinimum min = migrad();
        
        if(verbosity > 0) {
            std::cout << "HesseFailed: " << min.HesseFailed() << std::endl;
            std::cout << "HasCovariance: " << min.HasCovariance() << std::endl;
            std::cout << "HasValidCovariance: " << min.HasValidCovariance() << std::endl;
            std::cout << "HasValidParameters: " << min.HasValidParameters() << std::endl;
            std::cout << "IsAboveMaxEdm: " << min.IsAboveMaxEdm() << std::endl;
            std::cout << "HasReachedCallLimit: " << min.HasReachedCallLimit() << std::endl;
            std::cout << "HasAccurateCovar: " << min.HasAccurateCovar() << std::endl;
            std::cout << "HasPosDefCovar : " << min.HasPosDefCovar() << std::endl;
            std::cout << "HasMadePosDefCovar : " << min.HasMadePosDefCovar() << std::endl;
        }

        fcn_.get_params().set_variables(min.UserState());
        Minuit2::MnPrint::SetLevel(val);
        return min;
    }
    
};
    
    
}
}

