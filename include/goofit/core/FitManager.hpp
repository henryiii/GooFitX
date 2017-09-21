#pragma once

#include "Global.hpp"
#include <memory>
#include <vector>
#include "Variable.hpp"
#include "Registry.hpp"

namespace GooFit {
namespace experimental {

class ParameterList {
    std::shared_ptr<std::vector<Variable>> variables;
    
    ParameterList(Registry &registry) {
        
    }
    
};
    
    
    

}
}

