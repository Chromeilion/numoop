.. rach3datautils documentation master file, created by
   sphinx-quickstart on Sat Apr 22 15:49:17 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to numoop's documentation!
==========================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   ./sources/modules

To see some examples on how to use numoop, check out the scripts in the
examples dir.
Numoop provides two main modules:

Stats
   A module for working with tabular data. Provides the :class:`.DataFrame`
   class and :func:`.load` function. These allow you to work with any kind of
   tabular data easily and with great performance.
ODE
   A module for solving ordinary differential equations. Provides the classes
   :class:`.Euler`, :class:`.Midpoint` and :class:`.RK4` with the addition of
   their scalar implementations. Designed to work even with high precision data.



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
