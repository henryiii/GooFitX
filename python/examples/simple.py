#!/usr/bin/env python3

import numpy as np
from goofitx import Registry, Variable, Gauss, NLL, gauss_fcn

mean = 5.0
sig = 2.0

x = Registry(100000)
xvals = np.asarray(x)
xvals[:] = np.random.normal(mean, sig, size=100000)

mu = Variable("mu", 5.0)
sigma = Variable("sigma", 2.0)

gauss = Gauss(x,mu,sigma)

metric = NLL(gauss)
print("Automatic:", metric.calculate())


gauss_val = 1/np.sqrt(2*np.pi*sig**2) * np.exp(-(xvals-mean)**2/(2*sig**2))
nnl = -np.log(gauss_val)
print("Or, by hand:", np.sum(nnl))

o = gauss.output()
oval = np.asarray(o)

print("Gauss fcn:", gauss_fcn(xvals, mean, sig))
print("Guass automatic:", oval)
print("Gauss by hand:", gauss_val)


