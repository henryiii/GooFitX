#include <goofit/PDFs/simple/Gauss.hpp>
#include <goofit/Registry.hpp>
#include <goofit/Variable.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Gauss(py::module &m) {

    
    m.def("gauss_fcn",
          py::vectorize([](fptype x, fptype mu, fptype sigma){
                        return gauss_fcn(x, mu, sigma);}),
          "The gaussian function");
    
    
    py::class_<Gauss, PDF>(m, "Gauss")
        .def(py::init<Registry, Variable, Variable>())
    ;

}
