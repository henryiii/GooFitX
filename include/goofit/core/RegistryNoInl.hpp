#pragma once

#include <vector>
#include <memory>

#include "Global.hpp"


namespace GooFit {
namespace experimental {

class PDF;
struct OutputRegistry;

class Registry {
    /// The PDF that created this Registry (if one did)
    PDF* source {nullptr};
    
    std::shared_ptr<std::vector<fptype>> values;

    /// From a PDF
    Registry(PDF* source); // Inlined
    
    friend OutputRegistry; // Needs above constructor
    
public:
    /// New registry
    Registry(size_t n) : values(std::make_shared<std::vector<fptype>>(n)) {}

    
    // Standard tools for iteration
    // Standard caveat about a mutex hidden inside shared_ptr
    
    size_t size() const {return values->size();}
    auto begin() {return values->begin();}
    auto begin() const {return values->begin();}
    auto end() {return values->end();}
    auto end() const {return values->end();}
    fptype& at(size_t i) {return values->at(i);}
    const fptype& at(size_t i) const {return values->at(i);}
    fptype* data() {return values->data();}
    const fptype* data() const {return values->data();}
    
    /// Calclulate the source PDF
    void calculate();
    
    /// May be nullptr
    PDF* get_source() {return source;}


};

}
}
