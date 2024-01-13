import numoop

class TestODE:
    def test_init(self) -> None:
        # Init without anything
        def test_fun(i,j):
            return i+j
        eul = numoop.Euler_Scal(1)
        eul.set_func(test_fun)
        midp = numoop.Midpoint_Scal(2.)
        midp.set_func(test_fun)
