#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

#include "Global.hpp"
#include "PDF.hpp"

namespace GooFit {
namespace experimental {

class Registry;

class Metric {
protected:
    Registry* input;

public:
    Metric(Registry* input) : input(input) {}
    Metric(PDF &input) : input(input.output()) {}
    Metric(Metric&) = delete;
};

class NLL : public Metric {

public:
    using Metric::Metric;

    double calculate() {
        input->calculate();
        std::vector<double> outs(input->size());
        std::transform(input->begin(), input->end(), outs.begin(), [](fptype v){return -log(static_cast<double>(v));});
        return std::accumulate(outs.begin(), outs.end(), 0, std::plus<double>());
    }
};

}
}
