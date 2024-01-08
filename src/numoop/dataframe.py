from ._numoop import PyDataFrame
from typing import Literal


plot_types = Literal["hist", "pie", "line"]


class DataFrame(PyDataFrame):
    ...
