#include "Python.h"

#include "sudokusolver.h"

static PyObject *py_sudoku_solve(PyObject *self, PyObject *args)
{
    char *grid_repr_in;
    if (PyArg_ParseTuple(args, "s", grid_repr_in)) {
        char grid_repr_out[GRID_REPR_SIZE];

        if (sudoku_solve(grid_repr_in, grid_repr_out)) {
            PyObject *solution = Py_BuildValue("s", grid_repr_out);
            return solution;
        }
    }

    return Py_None;
}

static PyMethodDef methods[] = {
    { "sudoku_solve", py_sudoku_solve, METH_VARARGS, "Solves Sudoku." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef module_data = {
    PyModuleDef_HEAD_INIT,
    "sudokusolver",
    "A fast implementation of a Sudoku solver.",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_sudokusolver(void)
{
    return PyModule_Create(&module_data);
}