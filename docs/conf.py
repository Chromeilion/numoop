# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
import os
import sys

sys.path.insert(0, os.path.abspath(".."))

project = 'numoop'
copyright = '2024, Christian Špringer, Uros Zivanovic'
author = 'Christian Špringer, Uros Zivanovic'
release = '0.0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ["sphinx.ext.autodoc", "sphinx.ext.napoleon",
              "sphinx.ext.intersphinx"]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
autoclass_content = 'both'
autodoc_default_options = {
    "members": True,
    "show-inheritance": True,
    "inherited-members": True
}


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

# -- Options for Intersphinx -------------------------------------------------
intersphinx_mapping = {
    "numpy": ('https://numpy.org/doc/stable/', None),
    "python": ('https://docs.python.org/3/', None)
}
intersphinx_disabled_reftypes = ["std:*", "cpp:*"]
