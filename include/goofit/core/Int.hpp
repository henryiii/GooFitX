#pragma once

#include <string>
#include <iostream>

#include "Global.hpp"

namespace GooFit {
namespace experimental {
    
/// Read only integers
class Int {
    friend std::ostream& operator<< (std::ostream& out, const Int& pdf);
    
    int value_;
    
public:
    Int(int value) : value_(value) {}
    
    // Can be copied or moved (internal struct stays the same memory location)
    Int(const Int&) = default;
    Int(Int&&) = default;
    Int& operator=(Int&) = default;
    Int& operator=(Int&&) = default;
    
    int get_value() const {return value_;}
    
    operator int() const {return get_value();}
    
    std::string __repr__() const {
        return "Int(" + std::to_string(get_value()) + ")";
    }
    
};
    
inline std::ostream& operator<< (std::ostream& out, const Int& var) {
    return out << "Int : " << var.get_value() << std::endl;
}
    
}
}
