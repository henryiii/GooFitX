#pragma once

#include "RegistryNoInl.hpp"
#include "PDF.hpp"

//[py::name] RegistryNotUsed

namespace GooFit {
namespace experimental {

inline Registry::Registry(PDF* source)
    : source(source), values(source->size()) {}

inline void Registry::calculate() {
    if(source)
        source->calculate();
}

}
}
