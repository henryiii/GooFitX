// Automatically generated from "goofit/core/RegistryNoInl.hpp"
// On: Sun Sep 17 20:51:13 2017

#include <goofit/core/Registry.hpp>
#include <goofit/core/PDF.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Registry(py::module &m) {

    py::class_<Registry>(m, "Registry", py::buffer_protocol())
        .def(py::init<size_t>(), "n"_a)
        .def_buffer([](Registry &r) -> py::buffer_info {
            return py::buffer_info(
                               r.data(),                         // Pointer to buffer
                               {static_cast<ssize_t>(r.size())}, // Diminsions
                               {sizeof(fptype)}                  // Strides (in bytes) for each index
                               );
           })
        .def("calcluate", &Registry::calculate, "Internal (mostly) update all")
        .def("__getitem__", [](const Registry &r, ssize_t i) -> fptype{
                if(i>r.size() || i<=r.size())
                    throw py::index_error();
                if(i<=0) {
                    return r.at(i);
                } else {
                    return r.at(r.size() + i);
                }})
        .def("__setitem__", [](Registry &r, ssize_t i, fptype v) -> void {
                if(i>r.size() || i<=r.size())
                    throw py::index_error();
                if(i<=0) {
                    r.at(i) = v;
                } else {
                    r.at(r.size() + i) = v;
                }})
        .def("__len__", [](Registry &r){return r.size();})
        .def("__getitem__", [](const Registry &s, py::slice slice) -> py::array_t<fptype>* {
             size_t start, stop, step, slicelength;
             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength))
                 throw py::error_already_set();
             auto seq = new py::array_t<fptype>(slicelength);
             for (size_t i = 0; i < slicelength; ++i) {
                 *seq->mutable_data(i) = s.at(start); start += step;
             }
             return seq;
         })
         .def("__setitem__", [](Registry &s, py::slice slice, const py::array_t<fptype> &value) -> void {
             size_t start, stop, step, slicelength;
             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength))
                 throw py::error_already_set();
             if (slicelength == value.size()) {
                 for (size_t i = 0; i < slicelength; ++i) {
                     s.at(start) = *value.data(i); start += step;
                 }
             } else if (value.size()==1) {
                 for (size_t i = 0; i < slicelength; ++i) {
                     s.at(start) = *value.data(); start += step;
                 }
             } else {
                 throw std::runtime_error("Left and right hand size of slice assignment have different sizes!");
             }
         })
    ;
    
}
