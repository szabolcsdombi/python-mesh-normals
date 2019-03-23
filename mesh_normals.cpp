#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "glm/glm.hpp"

inline glm::vec3 & vertex(void * ptr, int stride, int idx) {
    return *(glm::vec3 *)(((char *)ptr) + stride * idx);
}

PyObject * meth_build_normals(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"mesh", "index", "stride", NULL};

    Py_buffer mesh;
    Py_buffer index;
    int stride;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y*y*i", keywords, &mesh, &index, &stride)) {
        return 0;
    }

    glm::ivec3 * triangles = (glm::ivec3 *)index.buf;
    int num_triangles = (int)(index.len / sizeof(glm::ivec3));
    int num_vertices = (int)(mesh.len / stride);

    PyObject * res = PyBytes_FromStringAndSize(NULL, sizeof(glm::vec3) * num_vertices);
    glm::vec3 * normals = (glm::vec3 *)PyBytes_AS_STRING(res);
    memset(normals, 0, sizeof(glm::vec3) * num_vertices);

    for (int i = 0; i < num_triangles; ++i) {
        const glm::vec3 & a = vertex(mesh.buf, stride, triangles[i].x);
        const glm::vec3 & b = vertex(mesh.buf, stride, triangles[i].y);
        const glm::vec3 & c = vertex(mesh.buf, stride, triangles[i].z);
        const glm::vec3 ab = glm::normalize(a - b);
        const glm::vec3 bc = glm::normalize(b - c);
        const glm::vec3 ca = glm::normalize(c - a);
        normals[triangles[i].x] += glm::normalize(glm::cross(ca, ab)) * acosf(-glm::dot(ca, ab));
        normals[triangles[i].y] += glm::normalize(glm::cross(ab, bc)) * acosf(-glm::dot(ab, bc));
        normals[triangles[i].z] += glm::normalize(glm::cross(bc, ca)) * acosf(-glm::dot(bc, ca));
    }

    for (int i = 0; i < num_vertices; ++i) {
        normals[i] = glm::normalize(normals[i]);
    }

    PyBuffer_Release(&index);
    PyBuffer_Release(&mesh);
    return res;
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
