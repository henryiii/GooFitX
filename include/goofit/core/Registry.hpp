#pragma once

#include "RegistryNoInl.hpp"
#include "PDF.hpp"

namespace GooFit {
namespace experimental {

    inline Registry::Registry(PDF* source)
    : source(source), values(std::make_shared<std::vector<fptype>>(source->size())) {}

inline void Registry::calculate() {
    if(source != nullptr)
        source->calculate();
}

}
}
