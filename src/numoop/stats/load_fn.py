from numoop._numoop import py_load
from .dataframe import DataFrame
from typing import Optional, Callable
from numoop.types import sup_row_types


def load(filepath: str,
         dataframe: Optional[DataFrame] = None,
         header: bool | None = None,
         columns: list[int] | None = None,
         col_types: list[Callable[[str], sup_row_types]] | None = None,
         newline_delimiter: str | None = None,
         column_delimiter: str | None = None) -> DataFrame:
    """
    Load a CSV file into a DataFrame object.

    Parameters
    ----------
    filepath : str
    dataframe : :class:`.DataFrame`, optional
    header : bool
        Whether the CSV file has a header.
    columns : list[int], optional
        What specific columns should be loaded from the file.
    col_types : list[Callable[Any, str]]
        A list of functions to be used when converting strings to numeric types.
    newline_delimiter : str
    column_delimiter : str

    Returns
    -------
    df : numoop.DataFrame
    """
    if dataframe is None:
        dataframe = DataFrame()
    # We can simply supply the load function with our python dataframe and
    # everything works as if it was the C++ version.
    py_load(
        filepath, dataframe, header, columns, col_types, newline_delimiter,
        column_delimiter
    )
    return dataframe
