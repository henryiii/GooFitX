import numpy as np
from goofitx import Registry, Variable, Gauss, NLL


x = Registry(100000)
xvals = np.asarray(x)
xvals[:] = np.random.normal(5.0, 2.0, size=100000)

mu = Variable("mu", 5.0)
sigma = Variable("sigma", 2.0)

gauss = Gauss(x,mu,sigma)

metric = NLL(gauss)
print(metric.calculate())
