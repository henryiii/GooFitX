#pragma once

#include "Global.hpp"
#include "Variable.hpp"
#include "Registry.hpp"

#include <set>

#include <Minuit2/FCNBase.h>
#include <Minuit2/MnUserParameterState.h>
#include <Minuit2/MnUserParameters.h>

namespace Minuit2 = ROOT::Minuit2;

namespace GooFit {
namespace experimental {

class FCN;
    
class Params : public Minuit2::MnUserParameters {
    friend FCN;
    
protected:
    std::set<Variable> vars_;
    
public:
    using MnUserParameters::MnUserParameters;
    
    Params(std::set<Variable> vars) : vars_(vars) {
        
        for(Variable var : vars_) {
            bool added;
            if(var.get_const()) {
                added = Add(var.get_name(), var.get_value());
            } else if(var.get_min() == var.get_max()) {
                added = Add(var.get_name(), var.get_value(), var.get_error());
            } else {
                added = Add(var.get_name(), var.get_value(), var.get_error(), var.get_min(), var.get_max());
            }
            
            if(!added)
                throw std::runtime_error("The name " + var.get_name() + " appears more than once!");
            
            var.set_index(Index(var.get_name()));
        }
    }
    
    // Read the values back into GooFit
    void set_variables(const Minuit2::MnUserParameterState &input) {
        for(const Variable &var_const : vars_) {
            // We promise not to touch the sorting key
            Variable& var = const_cast<Variable&>(var_const);
            
            size_t counter = var.get_index();
            var.set_value(input.Value(counter));
            var.set_error(input.Error(counter));
            SetValue(counter, var.get_value());
            SetError(counter, var.get_error());
        }
    }
    
    /// Make a parameter array with the current variable values
    std::vector<double> make_minuit_vector() const {
        // Reserve space for each parameter
        std::vector<double> minuitPars(size());
        
        // Get current value
        for(const Variable &var : vars_) {
            minuitPars.at(var.get_index()) = var.get_value();
        }
        return minuitPars;
    }
    
    /// Set from a minuit vector. Optional force_changed to force complete recalculation
    void from_minuit_vector(const std::vector<double> &values, bool force_changed=false) {
        for(Variable var : vars_) {
            var.set_value(values.at(var.get_index()));
            
            if(force_changed)
                var.set_changed(true);
        }
    }
    
    // Get the number of params in the fit
    size_t size() const { return vars_.size(); };
};

}
}

