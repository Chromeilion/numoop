from typing import TypeVar


_T = TypeVar("_T")
_T2 = TypeVar("_T2")


def get_key(m: dict[_T, _T2], val: _T2) -> _T:
    """
    A helper function for getting the key given a dictionary value. Mainly
    useful with DataFrame cat maps.
    """
    return list(m.keys())[list(m.values()).index(val)]
