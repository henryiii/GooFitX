#!/usr/bin/env python
from __future__ import print_function, division
import re
import sys
import time

try:
    from pathlib import Path # Built-in for python 3, pip install pathlib2 for python 2
except ImportError:
    from pathlib2 import Path

LINE = re.compile(r'^//\[([a-zA-Z:]+)\](.*)$')
PATH = Path(__file__).resolve().parent

def make_binding(filename):
    out = ''
    filepath = Path(filename)
    name = filepath.stem
    with filepath.open() as f:
        for line in f:
            res = LINE.match(line)
            if res:
                if res.group(1) == 'py':
                    out += '    ' + (res.group(2)[1:] if res.group(2).startswith(' ') else res.group(2)) + '\n'
                if res.group(1) == 'module::name':
                    name = res.group(2).strip()

    return '''\
// Automatically generated from "{filename}"
// On: {time}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_{name}(py::module &m) {{
{out}
}}
'''.format(name=name,out=out,filename=filename.resolve().relative_to(PATH), time=time.strftime("%c"))


if __name__ == "__main__":
    print(make_binding(sys.argv[1]))
