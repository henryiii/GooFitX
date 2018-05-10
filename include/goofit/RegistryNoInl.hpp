#pragma once

#include <vector>
#include <memory>
#include <set>

#include <vexcl/vexcl.hpp>

#include "Global.hpp"

namespace GooFit {
namespace experimental {

class PDF;
struct OutputRegistry;
class Variable;

class Registry {
    /// The PDF that created this Registry (if one did)
    PDF* source {nullptr};
    
    std::shared_ptr<vex::vector<fptype>> values;

    /// From a PDF
    Registry(PDF* source); // Inlined
    
    friend OutputRegistry; // Needs above constructor
    
public:
    /// New registry
    Registry(size_t n) : values(std::make_shared<vex::vector<fptype>>(n)) {}

    /// Note that in the std lib, uniqueness comes from this function
    bool operator < (const Registry& var) const {
        return values.get() < var.values.get();
    }
    
    /// Most programmers probably perfer this one
    bool operator == (const Registry& var) const {
        return values.get() == var.values.get();
    }
    
    // Standard tools for iteration
    // Standard caveat about a mutex hidden inside shared_ptr
    
    size_t size() const {return values->size();}
    auto begin() {return values->begin();}
    auto begin() const {return values->begin();}
    auto end() {return values->end();}
    auto end() const {return values->end();}
    vex::vector<fptype>& data() {return *values;}
    const vex::vector<fptype>& data() const {return *values;}
    
    /// Calclulate the source PDF
    void calculate();
    
    /// May be nullptr
    PDF* get_source() {return source;}
    
    /// All variables this registry depends on
    std::set<Variable> get_variables_recursive();
    
    /// Set all daughter variables's changed status to value
    void set_changed_recursive(bool value);
    
    /// All PDFs this registry depends on
    std::set<PDF*> get_pdfs_recursive();


};

}
}
