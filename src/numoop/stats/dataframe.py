from __future__ import annotations
from numoop._numoop import PyDataFrame
from numoop.types import sup_col_arr_types
from typing import Literal, Optional, Any, TypeVar, Callable, ParamSpec
import matplotlib.pyplot as plt
import matplotlib.figure as mpf
import matplotlib.axes._axes as mpa
import numpy as np
from functools import wraps

plot_types = Literal["hist", "pie", "line", "bar"]
T = TypeVar("T")
P = ParamSpec("P")


def _check_is_int(f: Callable[P, T]) -> Callable[P, T]:
    """Decorator to check if the passed column has an int datatype.
    """
    @wraps(f)
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> T:
        col = args[0].view(args[1])  # type:ignore
        if not np.issubdtype(col.dtype, np.integer):
            raise TypeError("Cannot make a bar chart with a non-int "
                            "column.")
        return f(*args, **kwargs)
    return wrapper


class DataFrame(PyDataFrame):
    """
    Class for storing tabular data. Stores data in C++ and provides access
    through NumPy arrays. Also provides various utility functions for working
    with the data.
    """

    _PLOT_RETURN_TYPE = tuple[mpf.Figure, mpa.Axes]

    def make_plot(self, idx: int, plot_type: str,
                  **kwargs: Any) -> _PLOT_RETURN_TYPE:
        """
        Plot a column with matplotlib. Supported plots are hist, pie, bar,
        and line.

        Parameters
        ----------
        idx : int
            Index of the column to plot
        plot_type : str
            one of hist, pie, or line
        **kwargs : dict
            Additional arguments passed when plotting

        Returns
        -------
        figure : matplotlib.pyplot.Figure
        axes : matplotlib.pyplot.Axes
        """
        match plot_type:
            case "hist":
                return self._make_hist(idx, **kwargs)
            case "pie":
                return self._make_pie(idx, **kwargs)
            case "line":
                return self._make_line(idx, **kwargs)
            case "bar":
                return self._make_bar(idx, **kwargs)
            case _:
                raise AttributeError(f"Unsupported plot type: {plot_type}, "
                                     f"provided.")

    def _make_hist(self, idx: int, **kwargs: Any) -> _PLOT_RETURN_TYPE:
        col = self.view(idx)
        counts, bins = np.histogram(col)
        fig, ax = plt.subplots()
        ax.stairs(counts, bins, **kwargs)
        ax.set_title(self.get_lab(idx))
        return fig, ax

    @_check_is_int
    def _make_bar(self, idx: int, **kwargs: Any) -> _PLOT_RETURN_TYPE:
        col = self.view(idx)
        x = self._get_cat_map_vals(idx)
        if x is None:
            x = [str(i) for i in list(range(len(np.unique(col))))]

        _, counts = np.unique(col, return_counts=True)

        fig, ax = plt.subplots()
        ax.bar(x, height=counts, **kwargs)
        ax.set_title(self.get_lab(idx))
        return fig, ax

    @_check_is_int
    def _make_pie(self, idx: int, **kwargs: Any) -> _PLOT_RETURN_TYPE:
        kwargs.setdefault("labels", self._get_cat_map_vals(idx))
        col = self.view(idx)
        _, counts = np.unique(col, return_counts=True)
        self._set_labels_range(col, **kwargs)

        fig, ax = plt.subplots()
        ax.pie(counts, **kwargs)
        ax.set_title(self.get_lab(idx))
        return fig, ax

    def _make_line(self, idx: int, **kwargs: Any) -> _PLOT_RETURN_TYPE:
        col = self.view(idx)

        fig, ax = plt.subplots()
        ax.plot(list(range(col.shape[0])), col, **kwargs)
        ax.set_title(self.get_lab(idx))
        return fig, ax

    def _get_cat_map_vals(self, idx: int) -> Optional[list[str]]:
        """Check if a category map exists for a column and return the sorted
        values if it does. None otherwise.
        """
        x = self.get_map(idx)
        if x:
            return [i[1] for i in sorted(list(x.items()), key=lambda it: it[0])]
        return None

    @staticmethod
    def _set_labels_range(col: sup_col_arr_types, **kwargs: Any) -> None:
        if kwargs["labels"] is None:
            kwargs["labels"] = list(range(len(np.unique(col))))

    def get_lab(self, idx: int) -> str | None:
        """
        Get the label for a column if it exists, otherwise return None.

        Parameters
        ----------
        idx : int

        Returns
        -------
        label : str, optional
        """
        if self.column_labels is not None:
            return self.column_labels[idx]
        return None
