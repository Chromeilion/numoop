import numoop
import numpy as np

def check_results(res,csv_file_path):
    # Load the reference
    csv_array = np.loadtxt(csv_file_path, delimiter=',', skiprows=1)
    csv_array = csv_array[:, 1:]
    print(type(csv_array))
    print(csv_array.shape)
    #csv_array = np.reshape(csv_array, res.shape)
    #print(res.shape)
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
    def test_init(self) -> None:
        # Init without anything
        def test_fun(i,j):
            return i+j
        eul = numoop.Euler_Scal(test_fun, 1, 0.05, 0.5)
        res = eul.ode()
        csv_file_path = '/home/sebas/Documents/chris/adv_prog/hm2/numoop/tests/csvtests/euler_scalar.csv'
        check_results(res,csv_file_path)

TestODE().test_init()
