# python-mesh-normals

A simple module to calculate mesh normals for python.

## Install

This module is **not available through pip**, it was designed to be forked and extended. Simplicity is a key goal in design. This module is using [glm](https://glm.g-truc.net/) and the Python's [c-api](https://docs.python.org/3/c-api/). The implementation can be found in the [mesh_normals.cpp](mesh_normals.cpp).

```
git clone https://github.com/cprogrammer1994/python-mesh-normals
cd python-mesh-normals
python setup.py develop
```

## Cheat Sheet

```py
import mesh_normals

# vertices
mesh = np.array([
    [1.0, 0.0, 0.0],
    [0.0, 1.0, 0.0],
    [0.0, 0.0, 1.0],
], dtype='f4')

# faces
index = np.array([
    [0, 1, 2],
], dtype='i4')

normals = mesh_normals.build_normals(mesh=mesh, index=index, stride=12)
# stride is the number of bytes to skip in mesh to get a new vertex
# normals is a bytes object

normals_array = np.frombuffer(normals, dtype='f4').reshape(-1, 3)
```
