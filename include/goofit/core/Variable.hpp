#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "Global.hpp"

namespace GooFit {
namespace experimental {

class Params;
    
struct SharedVariable {
    double value_;
    double error_;
    double min_;
    double max_;
    double blind_ {0.};
    int index {-1}; //< Assigned by Minuit through FitManager
    bool const_;
    bool changed {true};
    
    SharedVariable(double value_, double error_, double min_, double max_, bool const_)
    : value_(value_), error_(error_), min_(min_), max_(max_), const_(const_) {}
};
    
class Variable {
    friend std::ostream& operator<< (std::ostream& out, const Variable& pdf);
    friend Params;
    
    /// Name is locked at creation
    const std::string name_;
    
    /// The object of the pointer is unique (but Variable itself can be copied)
    std::shared_ptr<SharedVariable> self_;

    /// This is only used by FitManager
    void set_index(int value) { self_->index = value;}

public:
    /// New fixed variable (but with option to make constant without signature change)
    Variable(std::string name, double value, double error, double min, double max, bool const_ = false)
    : name_(name), self_(std::make_shared<SharedVariable>(value, error, min, max, const_)) {}
    
    /// New constant Variable
    Variable(std::string name, double value) : Variable(name, value, 0, 0, 0, true) {}
    
    /// New free Variable
    Variable(std::string name, double value, double error, bool const_ = false) : Variable(name, value, error, 0, 0, const_) {}

    // Can be copied or moved (internal struct stays the same memory location)
    Variable(const Variable&) = default;
    Variable(Variable&&) = default;
    Variable& operator=(const Variable&) = default;
    Variable& operator=(Variable&&) = default;

    /// Note that in the std lib, uniqueness comes from this function
    bool operator < (const Variable& var) const {
        return self_.get() < var.self_.get();
    }
    
    /// Most programmers probably perfer this one
    bool operator == (const Variable& var) const {
        return self_.get() == var.self_.get();
    }
    
    std::string get_name() const {return name_;}

    // Note that the following getters/setters access the value through
    // the shared_ptr, and therefore incur a mutex lock penalty
    // Fast access to value needs to be granted
    
    double get_value() const {return self_->value_;}
    void set_value(double value) {
        if(self_->value_ != value) {
            self_->value_ = value;
            self_->changed = true;
        }
    }
   
    double get_blind() const {return self_->blind_;}
    void set_blind(double value) {self_->blind_ = value;}
    
    double get_error() const {return self_->error_;}
    void set_error(double value) {self_->error_ = value;}
    
    double get_min() const {return self_->min_;}
    void set_min(double value) {self_->min_ = value;}
    
    double get_max() const {return self_->max_;}
    void set_max(double value) {self_->max_ = value;}

    bool get_const() const {return self_->const_;}
    void set_const(bool value) {self_->const_ = value;}
    
    int get_index() const {return self_->index;}
    
    bool get_changed() const {return self_->changed;}
    void set_changed(bool value) {self_->changed = value;}
    
    std::string __repr__() const {
        std::string out = "Variable(\"" + get_name() + "\", " +std::to_string(get_value());
        if(!get_const()) {
            out += ", " + std::to_string(get_error());
            if(get_min() != get_max())
                 out += ", " + std::to_string(get_min())
                      + ", " + std::to_string(get_min());
        }
        return out + ")";
    }
    
    operator double() const {return get_value();}
    double operator =(double value) {set_value(value); return value;}
};

inline std::ostream& operator<< (std::ostream& out, const Variable& var) {
    out << var.get_name() << " = " << var.get_value();
    if(var.get_error()>0)
        out << " +/- " << var.get_error();
    if(!var.get_const())
        out << " [" << var.get_min() << ", " << var.get_max() << "]";
    return out;
}
    
}
}
