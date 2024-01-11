from ._numoop import PyDataFrame
from typing import Literal, Optional
import matplotlib.pyplot as plt
import numpy as np


plot_types = Literal["hist", "pie", "line", "bar"]


class DataFrame(PyDataFrame):
    def make_plot(self, idx: int, plot_type: str) -> None:
        """
        Plot a column with matplotlib. Supported plots are hist, pie, and line.

        Parameters
        ----------
        idx : int
            Index of the column to plot
        plot_type : str
            one of hist, pie, or line
        """
        match plot_type:
            case "hist":
                self._make_hist(idx)
            case "pie":
                self._make_pie(idx)
            case "line":
                self._make_line(idx)
            case "bar":
                self._make_bar(idx)
            case _:
                raise AttributeError(f"Unsupported plot type: {plot_type}, "
                                     f"provided.")
        plt.show()

    def _make_hist(self, idx: int) -> None:
        col = self.view(idx)
        counts, bins = np.histogram(col)
        plt.stairs(counts, bins)

    def _make_bar(self, idx: int) -> None:
        col = self.view(idx)

        if not np.issubdtype(col.dtype, np.integer):
            raise AttributeError("Cannot make a bar chart with a non-int "
                                 "column.")

        x = self._get_cat_map_vals(idx)
        if x is None:
            # No labels, we just use numbers.
            x = list(range(len(np.unique(col))))

        _, counts = np.unique(col, return_counts=True)
        plt.bar(x, counts)

    def _make_pie(self, idx: int) -> None:
        ...

    def _make_line(self, idx: int, **kwargs) -> None:
        col = self.view(idx)
        plt.plot(list(range(col.shape[0])), col, **kwargs)

    def _get_cat_map_vals(self, idx) -> Optional[list[str]]:
        """Check if a category map exists for a column and return the sorted
        values if it does. None otherwise.
        """
        x = self.get_map(idx)
        if x:
            return [i[1] for i in sorted(list(x.items()), key=lambda it: it[0])]
        return None
        