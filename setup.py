from setuptools import Extension, setup

ext = Extension(
    name='mesh_normals',
    sources=['mesh_normals.cpp'],
)

setup(
    name='mesh_normals',
    version='0.1.0',
    ext_modules=[ext],
)
