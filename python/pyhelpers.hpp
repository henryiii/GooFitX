#pragma once

#include <sstream>

template<typename T>
std::string ostream_to_str(const T& self) {
    std::stringstream out;
    out << self;
    return out.str();
}
