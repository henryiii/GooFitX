#!/usr/bin/env python
from __future__ import print_function, division
import re
import sys
import time

try:
    from pathlib import Path # Built-in for python 3, pip install pathlib2 for python 2
except ImportError:
    from pathlib2 import Path

LINE = re.compile(r'^(\s*)//\[([a-zA-Z:]+)\](.*)$')
PATH = Path(__file__).resolve().parent

def make_binding(filename, outname):
    out = ''
    headers = ''
    filename = Path(filename)
    outname = Path(outname)
    name = filename.stem
    with filename.open() as f:
        for line in f:
            res = LINE.match(line)
            if res:
                if res.group(2) == 'py':
                    out += res.group(1) + (res.group(3)[1:] if res.group(3).startswith(' ') else res.group(3)) + '\n'
                elif res.group(2) == 'py::name':
                    name = res.group(3).strip()
                elif res.group(2) == 'py::header':
                    headers += '#include<' + res.group(3).strip() + ">\n"

    output = '''\
// Automatically generated from "{filename}"
// On: {time}

#include <{filename}>
#include <pybind11/pybind11.h>
{headers}

namespace py = pybind11;
using namespace pybind11::literals;

void init_{name}(py::module &m) {{
{out}
}}
'''.format(name=name,
           out=out,
           headers=headers,
           filename=filename.resolve().relative_to(PATH.parent / 'include'),
           time=time.strftime("%c"))

    if hasattr(output, 'decode'):
        output = output.decode('ASCII')

    if not outname.parent.exists():
        outname.parent.mkdir(parents=True)

    with outname.open('w') as f:
        f.write(output)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: make_bindings.py input output")
    make_binding(sys.argv[1], sys.argv[2])
