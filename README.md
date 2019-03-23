# python-bezier

A simple module to get the points of a cubic bezier curve for python.

## Install

This module is **not available through pip**, it was designed to be forked and extended. Simplicity is a key goal in design. This module is using [glm](https://glm.g-truc.net/) and the Python's [c-api](https://docs.python.org/3/c-api/). The implementation can be found in the [bezier.cpp](bezier.cpp).

```
git clone https://github.com/cprogrammer1994/python-bezier
cd python-bezier
python setup.py develop
```

## Cheat Sheet

```py
import bezier
```

# single curve

```py
a_pos = (0.0, 0.0, 0.0)
a_dir = (0.0, 1.0, 0.0)
b_pos = (1.0, 0.0, 0.0)
b_dir = (0.0, 1.0, 0.0)

point = bezier.curve(a_pos, a_dir, b_pos, b_dir, 0.2)
```

# multiple joined curves

```py
point_pairs = [
    [(0.0, 0.0, 0.0), (0.0, 1.0, 0.0)],
    [(1.0, 0.0, 0.0), (0.0, -1.0, 0.0)],
]

point = bezier.path(points=point_pairs, t=0.2, loop=True)
```
