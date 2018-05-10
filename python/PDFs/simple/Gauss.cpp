#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <goofit/PDFs/simple/Gauss.hpp>
#include <goofit/Registry.hpp>
#include <goofit/Variable.hpp>

namespace py = pybind11;
using namespace pybind11::literals;
using namespace GooFit::experimental;

void init_Gauss(py::module &m) {

    
    m.def("gauss_fcn",
          py::vectorize([](fptype x, fptype mu, fptype sigma){
            fptype result;
            gauss_fcn(result, x, mu, sigma);
            return result;
    }),
          "The gaussian function");
    
    
    py::class_<Gauss, PDF>(m, "Gauss")
        .def(py::init<Registry, Variable, Variable>())
    ;

}
