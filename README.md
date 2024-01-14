# numoop 
A header only C++ 17 library with Python bindings for working with statistics 
and ordinary differential equations, built on top of [Armadillo](https://arma.sourceforge.net/).

## What does numoop provide?
### DataFrame
The DataFrame object is similar to a Python Pandas dataframe. Each column is 
stored as an Armadillo Col object that can have its own type.
It's possible to have labels for each column which can also be used for indexing.
These features make a DataFrame perfect for working with various tabular data 
formats such as CSV files. 

The Python bindings for the DataFrame automatically convert Armadillo columns to 
NumPy arrays, as well as providing plotting functionality through matplotlib.
Because a column in a DataFrame is just an Armadillo/NumPy array, it's easy to 
use many statistical and numerical functions provided by these libraries. 

#### CSV Loader
Numoop also provides a function that can load a CSV file into a DataFrame for 
you. The function automatically detects all types present in the data and even 
converts all categorical columns to integers. If a header is present in the CSV, 
the function can also automatically read it into the DataFrame.

Everything is user controllable, if you'd like to specify the type of each 
column yourself, you can pass this to the function. It's also possible to only 
load selected columns from the file and to provide custom newline and columns 
separator chars. Loading only specific columns speeds up the loading process 
greatly.

### ODE Solvers
Numoop provides the following ordinary differential equation solvers:
 - Forward-Euler
 - Runge Kutta 4
 - Midpoint

All methods work with both vector and scalar inputs. The solution is saved to a 
CSV file and also returned from the function.
These solvers also all have Python bindings which work the same way as the C++ 
implementation.

### Considerations When Using the Python Bindings
When using the Python bindings, Armadillo columns are seamlessly mapped to 
NumPy arrays. When normally indexing, the returned array is a copy. If you'd 
like to have the best performance, use the .view() method, which returns a 
read-only view without copying any data.

## Using Numoop From C++
Since numoop is a header only library, using it is as simple as adding /src to 
your include directories. From here, if you want to use the whole module, you 
can include numoop.hpp. If you just want the stats module include stats/stats.hpp, 
and if you just want the ode module include ode/ode.hpp.

### Using the Python Bindings
Simply install the package by running the following command from the root of 
the repository:
```bash
pip install .
```
All the bindings will be compiled and the package will be installed in your 
currently active Python environment.

## Testing
The best way to test the package is through pytest with
[pytest-cpp](https://github.com/pytest-dev/pytest-cpp).

Install the package with testing extras and a permanant build directory.
```bash
SKBUILD_BUILD_DIR=build pip install .[test]
```
It's important to specify the build directory because this is where the compiled 
C++ tests are saved. Under normal circumstances these binaries get deleted once 
the build is complete.

Once the package is built and installed, all tests can be run from the project 
root with pytest:
```bash
pytest
```

## Performance and other considerations
The performance of numoop is highly dependent on the libraries present on the 
system it's being run on. Specifically, the implementation of BLAS and LAPACK.
Having a multi-threaded library such as OpenBLAS greatly improves the performance
of Armadillo and therefore numoop.

### Python Bindings Performance
In order to maintain memory safety, a copy operation must be performed when a 
column is indexed. Therefore, when accessing a column, it's preferable to use 
DataFrame.view, as this avoids copies. This does result in a read-only numpy 
array however.

## Credits
Numoop was created by Christian Špringer (christian.springer228@gmail.com) 
and Uros Zivanovic (chromeilion@outlook.com). Christian worked on the ODE module 
and Uros worked on the stats module. All collaboration was done through a 
repo on GitHub.
