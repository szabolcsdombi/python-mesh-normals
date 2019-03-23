#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "glm/glm.hpp"

PyObject * meth_build_normals(PyObject * self, PyObject * args, PyObject * kwargs) {
    Py_RETURN_NONE;
}

PyMethodDef module_methods[] = {
    {"build_normals", (PyCFunction)meth_build_normals, METH_VARARGS | METH_KEYWORDS, 0},
    {0},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "mesh_normals", 0, -1, module_methods, 0, 0, 0, 0};

extern "C" PyObject * PyInit_mesh_normals() {
    PyObject * module = PyModule_Create(&module_def);
    return module;
}
