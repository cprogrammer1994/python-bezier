from setuptools import Extension, setup

ext = Extension(
    name='bezier',
    sources=['bezier.cpp'],
)

setup(
    name='bezier',
    version='0.1.0',
    ext_modules=[ext],
)
