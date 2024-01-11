import numpy as np
import numpy.typing as npt
from typing import Sequence

# The internal types supported for each column
sup_col_types = (np.int32 | np.int64 | np.float32 | np.float64 | np.uint32 |
                 np.uint64 | np.complex64 | np.complex128 | complex | int |
                 float)
# Types supported when appending row-wise
sup_row_types = Sequence[sup_col_types]
# When specifying multiple rows at once
sup_multi_row_types = (Sequence[sup_row_types])
# Supported types of the actual arrays
sup_col_arr_types = (
        npt.NDArray[np.int32] | npt.NDArray[np.int64] |
        npt.NDArray[np.float32] | npt.NDArray[np.float64] |
        npt.NDArray[np.uint32] | npt.NDArray[np.uint64] |
        npt.NDArray[np.complex64] | npt.NDArray[np.complex128]
)
# Int to category for categorical cols
cat_dict = dict[int, str]
# Container for all cat dictionaries
all_cat_dict = dict[int, cat_dict]
