# numoop 
A header only C++ library for working with statistics and ordinary differential 
equations, built on top of [Armadillo](https://arma.sourceforge.net/).

## What does numoop provide?
### DataFrame
The DataFrame object is similar to a Python Pandas dataframe. Each column is 
stored as an Armadillo Col object that can have its own type.
It's possible to have labels for each column which can also be used for indexing.
These features make a DataFrame perfect for working with various tabular data 
formats such as CSV files. 

Because a column in a DataFrame is just an Armadillo array, it's easy to use 
many statistical and numerical functions provided by Armadillo with a numoop 
DataFrame. One limitation of this however, is that it's not possible to store 
non-numeric data in the DataFrame. To get around this, categorical data must be 
converted to ints. The DataFrame object has methods for getting and setting a 
map which can map integer values to categories (strings).

#### CSV Loader
Numoop also provides a function that can load a CSV file into a DataFrame for 
you. The function automatically detects all types present in the data and even 
converts all categorical columns to integers. If a header is present in the CSV, 
the function can also automatically read it into the DataFrame.

Everything is user controllable, if you'd like to specify the type of each 
column yourself, you can pass this to the function. It's also possible to only 
load selected columns from the file and to provide custom newline and columns 
separator chars.

### ODE Solvers
Numoop provides the following ordinary differential equation solvers:
 - Forward-Euler
 - Runge Kutta 4
 - Midpoint

All methods work with both vector and scalar inputs. The solution is saved to a 
CSV file and also returned from the function.
