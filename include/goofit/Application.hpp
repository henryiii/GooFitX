#pragma once

#include <string>
#include <iostream>

#include <vexcl/vexcl.hpp>

#include "Global.hpp"

namespace GooFit {
namespace experimental {
    
/// Application for goofit
class Application {
    vex::Context ctx;

public:
    Application() : ctx(vex::Filter::CPU) {}
    
};
    
}
}
