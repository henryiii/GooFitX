#pragma once

#include "RegistryNoInl.hpp"
#include "PDFs/PDF.hpp"
#include "Variable.hpp"

namespace GooFit {
namespace experimental {

inline Registry::Registry(PDF* source)
    : source(source), values(std::make_shared<std::vector<fptype>>(source->size())) {}

inline void Registry::calculate() {
    if(source != nullptr)
        source->calculate();
}

inline std::set<Variable> Registry::get_variables_recursive() {
    if(source != nullptr)
        return source->get_variables_recursive();
    else return {};
}
    
inline std::set<PDF*> Registry::get_pdfs_recursive() {
    if(source != nullptr) {
        std::set<PDF*> values = source->get_pdfs_recursive();
        values.insert(source);
        return values;
    } else
        return {};

}
    
    inline void Registry::set_changed_recursive(bool value) {
    std::set<Variable> vars = get_variables_recursive();
    for(Variable x : vars)
        x.set_changed(value);
}
    
}
}
