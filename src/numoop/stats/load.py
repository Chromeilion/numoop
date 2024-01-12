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
         column_delimiter: str | None = None) -> tuple[list[str], DataFrame]:
    """
    Load a CSV file into a DataFrame object.

    Parameters
    ----------
    filepath : str
    dataframe : numoop.DataFrame, optional
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
    types : list[str]
    The column types that were autodetected when loading the CSV.
    df : numoop.DataFrame
    """
    if dataframe is None:
        dataframe = DataFrame()
    # We can simply supply the load function with our python dataframe and
    # everything works as if it was the C++ version.
    det_types = py_load(
        filepath, dataframe, header, columns, col_types, newline_delimiter,
        column_delimiter
    )
    return det_types, dataframe
