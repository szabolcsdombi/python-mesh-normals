import numpy as np

import mesh_normals

mesh = np.array([
    [0.0, 0.0, 0.0],
    [0.0, 1.0, 0.0],
    [1.0, 0.0, 1.0],
    [1.0, 1.0, 1.0],
    [2.0, 0.0, 0.0],
    [2.0, 1.0, 0.0],
], 'f4')

index = np.array([
    [1, 0, 2],
    [1, 2, 3],
    [3, 2, 4],
    [3, 4, 5],
], 'i4')

print(np.ndarray((6, 3), 'f4', mesh_normals.build_normals(mesh, index, 12)))
