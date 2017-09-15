#!/usr/bin/env python
from __future__ import print_function, division

from make_binding import Path, make_binding

PATH = Path(__file__).resolve().parent

def make_bindings():
    for fpath in (PATH / 'include/goofit/core').glob('*.hpp'):
        name = fpath.stem
        target = PATH / 'python/core' / fpath.with_suffix('.cpp').name
        output = make_binding(fpath)
        with target.open('w') as f:
            if(str is not unicode):
                output = output.decode('ASCII')
            f.write(output)

if __name__ == "__main__":
    make_bindings()
