import matplotlib
import matplotlib.pyplot as plt
import numpy as np

import bezier

fig, ax = plt.subplots()

curve = [bezier.path([[(0.0, 0.0, 0.0), (0.0, 1.414, 0.0)], [(1.0, 0.0, 0.0), (0.0, -1.414, 0.0)]], t, True) for t in np.linspace(0.0, 1.0, 200)]

ax.plot([x for x, y, z in curve], [y for x, y, z in curve])
ax.grid()
plt.show()
