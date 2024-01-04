from __future__ import annotations
import numpy.typing as npt
import numpy as np
import typing
__all__ = ['DataFrame', 'load']
class DataFrame:
    def __call__(self, arg0: str) -> npt.NDArray[np.float64] | npt.NDArray[np.complex128] | npt.NDArray[np.complex64] | npt.NDArray[np.uint64] | npt.NDArray[np.int64]:
        ...
    def __getitem__(self, arg0: int) -> npt.NDArray[np.float64] | npt.NDArray[np.complex128] | npt.NDArray[np.complex64] | npt.NDArray[np.uint64] | npt.NDArray[np.int64]:
        ...
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, data: list[list[float | complex | complex | int | int]], labels: list[str] | None = None) -> None:
        ...
    def __setitem__(self, arg0: int, arg1: npt.NDArray[np.float64] | npt.NDArray[np.complex128] | npt.NDArray[np.complex64] | npt.NDArray[np.uint64] | npt.NDArray[np.int64]) -> None:
        ...
    def get_map(self, arg0: int) -> dict[int, str]:
        ...
    def set_map(self, arg0: int, arg1: dict[int, str]) -> None:
        ...
    @property
    def column_labels(self) -> list[str] | None:
        ...
    @column_labels.setter
    def column_labels(self, arg1: list[str]) -> None:
        ...
    @property
    def shape(self) -> tuple[int, int]:
        ...
@typing.overload
def load(filepath: str, dataframe: DataFrame, header: bool | None = None, columns: list[int] | None = None, col_types: list[typing.Callable[[str], float | complex | complex | int | int]] | None = None, newline_delimiter: str | None = None, column_delimiter: str | None = None) -> list[str]:
    """
    Load a CSV into a DataFrame
    """
@typing.overload
def load(filepath: str, header: bool | None = None, columns: list[int] | None = None, col_types: list[typing.Callable[[str], float | complex | complex | int | int]] | None = None, newline_delimiter: str | None = None, column_delimiter: str | None = None) -> tuple[list[str], DataFrame]:
    """
    Load a CSV into a new DataFrame
    """
__version__: str = 'dev'
