#pragma once

#include <string>
#include <iostream>

#include <vexcl/vexcl.hpp>

#include <CLI/CLI.hpp>

#include "Global.hpp"

namespace GooFit {
namespace experimental {
    
/// Application for goofit
class Application : public CLI::App {
    vex::Context ctx{vex::Filter::CPU};

public:
    Application(std::string discription) : App(discription) {

        add_flag_function("--gpu", [this](size_t){
            this->ctx = vex::Context(vex::Filter::GPU);
        }, "Filter on GPU instead of CPU");
    }
};
    
}
}
