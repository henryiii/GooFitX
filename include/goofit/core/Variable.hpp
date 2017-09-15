#pragma once

#include <vector>
#include <string>

#include "Global.hpp"

namespace GooFit {
namespace experimental {

struct Variable {
    std::string name;
    fptype value;
    bool const_;
    fptype error {0};
    fptype min_ {0};
    fptype max_ {0};

public:
    /// New Variable
    Variable(std::string name, fptype value) : name(name), value(value), const_(true) {}

    /// Can't copy
    Variable(Variable&) = delete;

};

}
}
