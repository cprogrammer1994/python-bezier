import numpy as np
import pytest

import bezier


def test_last_point_loop():
    a_pos, a_dir = (0.0, 0.0, 0.0), (0.0, 1.414, 0.0)
    b_pos, b_dir = (1.0, 0.0, 0.0), (0.0, -1.414, 0.0)

    pt1 = bezier.path([(a_pos, a_dir), (b_pos, b_dir)], 0.0, loop=True)
    np.testing.assert_almost_equal(pt1, a_pos)

    pt2 = bezier.path([(a_pos, a_dir), (b_pos, b_dir)], 0.5, loop=True)
    np.testing.assert_almost_equal(pt2, b_pos)

    pt3 = bezier.path([(a_pos, a_dir), (b_pos, b_dir)], 1.0, loop=True)
    np.testing.assert_almost_equal(pt3, a_pos)


def test_last_point_no_loop():
    a_pos, a_dir = (0.0, 0.0, 0.0), (0.0, 1.414, 0.0)
    b_pos, b_dir = (1.0, 0.0, 0.0), (0.0, -1.414, 0.0)

    pt1 = bezier.path([(a_pos, a_dir), (b_pos, b_dir)], 0.0, loop=False)
    np.testing.assert_almost_equal(pt1, a_pos)

    pt3 = bezier.path([(a_pos, a_dir), (b_pos, b_dir)], 1.0, loop=False)
    np.testing.assert_almost_equal(pt3, b_pos)



if __name__ == '__main__':
    pytest.main([__file__])
