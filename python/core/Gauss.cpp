#include <goofit/core/Gauss.hpp>
#include <pybind11/pybind11.h>
#include<pybind11/numpy.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Gauss(py::module &m) {

    
    m.def("gauss_fcn",
          py::vectorize([](fptype x, fptype mu, fptype sigma){
                        fptype out; gauss_fcn(out, x, mu, sigma); return out;}),
          "The gaussian function");
    
    
    py::class_<Gauss>(m, "Gauss")
        .def(py::init<Registry&, Variable&, Variable&>(),
             py::keep_alive<1,2>(), py::keep_alive<1,3>(), py::keep_alive<1,4>() )
    ;

}
