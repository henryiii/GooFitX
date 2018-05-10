#pragma once

#include <memory>
#include <set>

#include "Global.hpp"
#include "Variable.hpp"
#include "Registry.hpp"
#include "Params.hpp"
#include "Log.hpp"

#include <vexcl/vexcl.hpp>

#include <Minuit2/FCNBase.h>
#include <Minuit2/MnUserParameterState.h>
#include <Minuit2/MnUserParameters.h>

namespace Minuit2 = ROOT::Minuit2;

namespace GooFit {
namespace experimental {

class FCN : public Minuit2::FCNBase {
protected:
    // These are safe to be mutable since this must be called from one thread
    
    mutable Registry output_;
    mutable Params params_;
    double up_ {.5};
    
public:
    /// Create an FCN given parameters (PDF reference is inside params)
    /// This currently assumes all variables are initalized to needing calculations
    FCN(Registry output) : output_(output), params_(output_.get_variables_recursive()) {}
    
    
    /// Run the fit (used by Minuit2 class)
    double operator()(const std::vector<double> &pars) const override;
    
    /// Produce the FCN value for the current values of the parameters
    double operator()() const {return calculate_nll();}
    
    /// Actually do the nnl calculation
    double calculate_nll() const;
    
    /// This value is 0.5 for ll, 1 for chi2
    double Up() const override { return up_; }
    
    /// Get a refernce to the parameters
    Params &get_params() {return params_;}
};
    
/// Run the fit (used by Minuit2 class)
inline double FCN::operator()(const std::vector<double> &pars) const {
    params_.from_minuit_vector(pars);
    
    return calculate_nll(); // Calculate nll
}
    

inline double FCN::calculate_nll() const {
    
    output_.calculate();
    
    // We have fully calculated the output
    output_.set_changed_recursive(false);
    
    vex::Reductor<double, vex::SUM> sum;
    double val = sum(-log(output_.data()));
    GOOFIT_DEBUG("FCN: {}", val);
    return val;
}

}
}

