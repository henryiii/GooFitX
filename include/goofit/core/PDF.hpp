#pragma once

#include <vector>
#include <stdexcept>
#include "Global.hpp"
#include "RegistryNoInl.hpp"
#include "Variable.hpp"

//[py::name] PDF

//[py] using namespace GooFit::experimental;
namespace GooFit {
namespace experimental {

struct InputVariable;
struct InputRegistry;
struct OutputRegistry;


    
//[py] py::class_<PDF>(m, "PDF")
class PDF {
protected:

    friend InputVariable;
    friend InputRegistry;
    friend OutputRegistry;

    std::vector<Registry*> inputs;
    std::vector<Registry*> outputs;
    std::vector<Variable*> variables;

    bool current {false};

public:
    //[py] .def(py::init<>())
    PDF() {}
    
    PDF(PDF&) = delete;

    //[py] .def("output", &PDF::output)
    Registry* output() {
        if(outputs.size()==1)
            return outputs[0];
        else
            throw std::runtime_error("The metric must be applied to a single output PDF");
    }

    //[py] .def("calculate", &PDF::calculate)
    virtual void calculate() {
        for(Registry* reg : inputs)
            reg->calculate();
    }

    //[py] .def("size", &PDF::size)
    size_t size() const {return inputs.at(0)->size();}
    
//[py] ;
};

// These structs help in making new PDF classes
    
struct InputVariable {
    Variable* value;

    InputVariable(PDF* self, Variable* value) : value(value) {
        self->variables.push_back(value);
    }

    operator fptype() const { return value->value; }
};

struct InputRegistry {
    Registry* value;

    InputRegistry(PDF* self, Registry* value) : value(value) {
        self->inputs.push_back(value);
    }

    Registry* operator ->() {return value;}
};

struct OutputRegistry {
    std::shared_ptr<Registry> value;

    OutputRegistry(PDF* self) : value(new Registry(self)) {
        self->outputs.push_back(value.get());
    }
    Registry* operator ->() {return value.get();}
};




}
}
