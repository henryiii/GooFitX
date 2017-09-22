#pragma once

#include <vector>
#include <set>
#include <iostream>
#include <stdexcept>
#include "../Global.hpp"
#include "../RegistryNoInl.hpp"
#include "../Int.hpp"
#include "../Variable.hpp"


namespace GooFit {
namespace experimental {

struct InputVariable;
struct InputRegistry;
struct OutputRegistry;
struct IntRegistry;


class PDF {
    friend std::ostream& operator<< (std::ostream& out, const PDF& pdf);
protected:

    friend InputVariable;
    friend InputRegistry;
    friend OutputRegistry;
    friend IntRegistry;

    // Once constructed, the inputs/output cannot change
    // (but the values in the pointers can)
    std::vector<Registry> inputs;
    std::vector<Registry> outputs;
    std::vector<Variable> variables;
    std::vector<Int> integers;
    
    std::string pdf_name;

public:
    PDF(std::string pdf_name) : pdf_name(pdf_name) {}
    
    PDF(const PDF&) = delete;
    
    Registry output() {
        if(outputs.size()==1)
            return outputs[0];
        else
            throw std::runtime_error("The metric must be applied to a single output PDF");
    }

    virtual void calculate() {
        for(Registry& reg : inputs)
            reg.calculate();
    }

    size_t size() const {return inputs.at(0).size();}
    
    std::vector<Registry> get_inputs() {return inputs;}
    std::vector<Registry> get_outputs() {return outputs;}
    std::vector<Variable> get_variables() {return variables;}
    std::vector<Int> get_integers() {return integers;}
    
    bool get_changed() {
        bool changed = false;
        std::set<Variable> vars = get_variables_recursive();
        for(Variable x : vars)
            changed |= x.get_changed();

        return changed;
    }
    
    std::set<Variable> get_variables_recursive() {
        std::set<Variable> vars;
        vars.insert(variables.begin(), variables.end());
        for(auto &registry : inputs) {
            auto tmp_inputs = registry.get_variables_recursive();
            vars.insert(tmp_inputs.begin(), tmp_inputs.end());
        }
        return vars;
    }
    
    std::set<PDF*> get_pdfs_recursive() {
        std::set<PDF*> out;
        for(auto &registry : inputs) {
            std::set<PDF*> tmp = registry.get_pdfs_recursive();
            out.insert(tmp.begin(), tmp.end());
        }
        return out;
    }
    
    /// Set all daughter variables's changed status to value
    void set_changed_recursive(bool value) {
        std::set<Variable> vars = get_variables_recursive();
        for(Variable x : vars)
            x.set_changed(value);
    }
    
    std::string __repr__() const {
        return std::to_string(inputs.size()) + " -> " + pdf_name
               + "(" + join<Variable>(variables, [](const Variable &v){return v.get_name();})
        + ") -> " + std::to_string(outputs.size());
    }
};
    
inline std::ostream& operator<< (std::ostream& out, const PDF& pdf) {
    out << "PDF: " << pdf.pdf_name << "\n";
    out << "  Variables:\n";
    for (const auto &var : pdf.variables)
        out << "    " << var << "\n";
    return out;
}

// These structs help in making new PDF classes
    
struct InputVariable {
    Variable value;

    InputVariable(PDF* self, Variable value) : value(value) {
        self->variables.push_back(value);
    }

    operator fptype() const { return value.get_value(); }
};

struct InputRegistry {
    Registry value;

    InputRegistry(PDF* self, Registry value) : value(value) {
        self->inputs.push_back(value);
    }

    Registry* operator ->() {return &value;}
};

struct OutputRegistry {
    Registry value;

    OutputRegistry(PDF* self) : value(self) {
        self->outputs.push_back(value);
    }
    
    Registry* operator ->() {return &value;}
};

struct IntRegistry {
    Int value;
    
    IntRegistry(PDF* self, Int value) : value(value) {
        self->integers.push_back(value);
    }
    
    Int* operator ->() {return &value;}

};


}
}
