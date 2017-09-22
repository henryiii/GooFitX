#!/usr/bin/env python3

import numpy as np
from goofitx import Registry, Variable, Gauss, FitManager, gauss_fcn

mean = 4.0
sig = 1.75
print("Real values: mu =", mean, "sigma =", sig)

x = Registry(100000)
x[:] = np.random.normal(mean, sig, size=100000)

mu = Variable("mu", 5.0, .01)
sigma = Variable("sigma", 2.0, .01)

print("Initial values:", mu, sigma)

gauss = Gauss(x,mu,sigma)

man = FitManager(gauss)
man.fit()
print("Fit values:", mu, sigma)


print("mu =", 3)
mu.value = 3
mu.error = .01

man.fit()
print("Fit values:", mu, sigma)

