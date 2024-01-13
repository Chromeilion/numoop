from __future__ import annotations

from ._numoop import __doc__, __version__
from .stats import DataFrame, load
from . import types

__all__: list[str] = ["__doc__", "__version__", "DataFrame", "load"]
