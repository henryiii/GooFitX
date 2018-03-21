
set(GOOFIT_PYTHON_SRC
    PDFs/PDF.cpp
    PDFs/simple/Gauss.cpp
    core/FCN.cpp
    core/FitManager.cpp
    core/Global.cpp
    core/Int.cpp
    core/Params.cpp
    core/Registry.cpp
    core/Variable.cpp
    )

pybind11_add_module(goofitx goofit.cpp pyhelpers.hpp ${GOOFIT_PYTHON_SRC} ${GOOFIT_HEADERS})
target_link_libraries(goofitx PUBLIC goofit)

