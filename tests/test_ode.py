from numoop.ode import Euler, EulerScal, MidpointScal, Midpoint, RK4Scal, RK4
from typing import Union, TypeVar, Callable
import numpy as np
import numpy.typing as npt
import os
import tempfile

all_methods = Union[Euler, EulerScal, MidpointScal, Midpoint,
RK4Scal, RK4]

_T = TypeVar("_T")


# Setting the parameters for testing
def scal_fun(i: float, j: float) -> float:
    return i + j


def vec_fun(i: float, j: npt.NDArray[np.float64]) -> npt.NDArray[np.float64]:
    return np.array([j[1], -j[0]])


y0_vec = np.array([0.0, 1.0])
y0_scal = 1.0
h = 0.05
end = 0.5


def check_results(res: npt.NDArray[np.float64], csv_file_path: str) -> bool:
    # Load the reference csv
    csv_array = np.loadtxt(csv_file_path, delimiter=',', skiprows=1)
    csv_array = csv_array[:, 1:]

    # Compare the NumPy arrays
    arrays_equal = np.array_equal(res, csv_array)

    if arrays_equal:
        return True
    else:
        approx_equal = np.allclose(res, csv_array, atol=1e-8)
        if approx_equal:
            return True
        else:
            return False


def do_test(method: all_methods, csv_filepath: str) -> None:
    old_dir = os.getcwd()
    with tempfile.TemporaryDirectory() as f:
        os.chdir(f)
        res = method.ode()
        csv_file_path = f"{old_dir}/{csv_filepath}"
        assert check_results(res, csv_file_path)
        os.chdir(old_dir)


class TestODE:
    def test_eulerscal(self) -> None:
        csv_file_path = 'tests/csvtests/euler_scalar.csv'
        do_test(EulerScal(scal_fun, y0_scal, h, end), csv_file_path)

    def test_eulervec(self) -> None:
        csv_file_path = 'tests/csvtests/euler_vector.csv'
        do_test(Euler(vec_fun, y0_vec, h, end), csv_file_path)

    def test_midpointscal(self) -> None:
        csv_file_path = 'tests/csvtests/midpoint_scalar.csv'
        do_test(MidpointScal(scal_fun, y0_scal, h, end), csv_file_path)

    def test_midpointvec(self) -> None:
        csv_file_path = 'tests/csvtests/midpoint_vector.csv'
        do_test(Midpoint(vec_fun, y0_vec, h, end), csv_file_path)

    def test_rk4scal(self) -> None:
        csv_file_path = 'tests/csvtests/rk4_scalar.csv'
        do_test(RK4Scal(scal_fun, y0_scal, h, end), csv_file_path)

    def test_rk4vec(self) -> None:
        csv_file_path = 'tests/csvtests/rk4_vector.csv'
        do_test(RK4(vec_fun, y0_vec, h, end), csv_file_path)
