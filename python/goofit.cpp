#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_Int(py::module &m);
void init_Variable(py::module &m);
void init_Registry(py::module &m);
void init_PDF(py::module &m);
void init_Gauss(py::module &m);
void init_Params(py::module &m);
void init_FCN(py::module &m);
void init_FitManager(py::module &m);

PYBIND11_MODULE(goofitx, m) {
    init_Int(m);
    init_Variable(m);
    init_Registry(m);
    init_PDF(m);
    init_Gauss(m);
    init_Params(m);
    init_FCN(m);
    init_FitManager(m);
}


