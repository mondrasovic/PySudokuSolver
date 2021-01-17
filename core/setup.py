from setuptools import Extension, setup

module = Extension(
    "sudokusolver",
    sources=[
        'pysudokusolver.c',
        'sudokusolver.c'
    ])

setup(name='sudokusolver',
     version='1.0',
     description='Python wrapper for a fast C Sudoku solver.',
     ext_modules=[module])
