import numoop
import numpy as np

#Setting the parameters for testing
def scal_fun(i,j):
    return i+j
    
def vec_fun(i,j):
    return np.array([j[1],-j[0]])
    
y0_vec = np.array([0.0, 1.0])
y0_scal = 1.0
h = 0.05
end = 0.5

def check_results(res,csv_file_path):
    # Load the reference csv
    csv_array = np.loadtxt(csv_file_path, delimiter=',', skiprows=1)
    csv_array = csv_array[:, 1:]

    # Compare the NumPy arrays
    arrays_equal = np.array_equal(res, csv_array)

    if arrays_equal:
        print("Both arrays contain the same values.")
    else:
        approx_equal = np.allclose(res, csv_array, atol=1e-8)
        if approx_equal:
            print("Approximately equal: Arrays are similar within the specified tolerance.")
        else:
            print("Arrays are different.")

class TestODE:
    
    def test_eulerscal(self) -> None:
        eul = numoop.Euler_Scal(scal_fun, y0_scal, h, end)
        res = eul.ode()
        csv_file_path = 'tests/csvtests/euler_scalar.csv'
        check_results(res,csv_file_path)
        
    def test_eulervec(self) -> None:
        eul = numoop.Euler(vec_fun, y0_vec, h, end)
        res = eul.ode()
        csv_file_path = 'tests/csvtests/euler_vector.csv'
        check_results(res,csv_file_path)

    def test_midpointscal(self) -> None:
        mpt = numoop.Midpoint_Scal(scal_fun, y0_scal, h, end)
        res = mpt.ode()
        csv_file_path = 'tests/csvtests/midpoint_scalar.csv'
        check_results(res,csv_file_path)
        
    def test_midpointvec(self) -> None:
        mpt = numoop.Midpoint(vec_fun, y0_vec, h, end)
        res = mpt.ode()
        csv_file_path = 'tests/csvtests/midpoint_vector.csv'
        check_results(res,csv_file_path)

    def test_rk4scal(self) -> None:
        rk4 = numoop.RK4_Scal(scal_fun, y0_scal, h, end)
        res = rk4.ode()
        csv_file_path = 'tests/csvtests/rk4_scalar.csv'
        check_results(res,csv_file_path)
        
    def test_rk4vec(self) -> None:
        rk4 = numoop.RK4(vec_fun, y0_vec, h, end)
        res = rk4.ode()
        csv_file_path = 'tests/csvtests/rk4_vector.csv'
        check_results(res,csv_file_path)


