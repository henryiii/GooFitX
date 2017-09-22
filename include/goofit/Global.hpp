#pragma once

#include <vector>
#include <functional>
#include <string>

namespace GooFit {
namespace experimental {

    using fptype = double;

    
    /// Join a series of value into a string seperated by sep
    template<typename T>
    std::string join(const std::vector<T>& val,
                     std::function<std::string(const T&)> func,
                     std::string sep=", ") {
        std::string out;
        for(auto &v : val)
            out += (out.empty() ? "" : sep) + func(v);
        return out;
    }
}
}
