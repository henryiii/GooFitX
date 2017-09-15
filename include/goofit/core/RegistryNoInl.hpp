#pragma once

#include <vector>
#include "Global.hpp"

namespace GooFit {
namespace experimental {

class PDF;

class Registry {
    PDF* source = nullptr;
    std::vector<fptype> values;

public:
    /// New registry
    Registry(size_t n) : values(n) {}

    /// From a PDF
    Registry(PDF* source); // Inlined

    // Standard tools for iteration
    
    size_t size() const {return values.size();}
    auto begin() {return values.begin();}
    auto begin() const {return values.begin();}
    auto end() {return values.end();}
    auto end() const {return values.end();}
    fptype& at(size_t i) {return values.at(i);}
    
    // Calclulate the source PDF
    void calculate();

};

}
}
