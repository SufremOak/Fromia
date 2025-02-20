from setuptools import setup
from Cython.Build import cythonize

setup(
    name="Fromia Graphical Runtime",
    ext_modules=cythonize("FWorkspace.pyx"),
    install_requires=["PyQt5"],
    zip_safe=False,
)