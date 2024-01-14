import numoop
import numpy as np


def fun(i, j):
    return i + j

eul = numoop.ode.Euler_Scal((fun, 1.0, 0.05, 0.5))
res = eul.ode()
csv_file_path = 'tests/csvtests/euler_scalar.csv'
print(res)


def fun(i, j):
    return np.array([j[1], -j[0]])


y0 = np.array([0.0, 1.0])
eul = numoop.ode.Euler((fun, y0, 0.05, 0.5))

res = eul.ode()
csv_file_path = 'tests/csvtests/euler_vector.csv'
print(res)
