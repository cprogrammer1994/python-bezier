#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "glm/glm.hpp"

#define v_xyz(obj) &obj.x, &obj.y, &obj.z

void get_point(glm::vec3 & v, PyObject * obj) {
    obj = PySequence_Fast(obj, "not iterable");
    if (!obj || PySequence_Fast_GET_SIZE(obj) != 3) {
        PyErr_Format(PyExc_ValueError, "invalid point");
        return;
    }
    PyObject ** items = PySequence_Fast_ITEMS(obj);
    v.x = (float)PyFloat_AsDouble(items[0]);
    v.y = (float)PyFloat_AsDouble(items[1]);
    v.z = (float)PyFloat_AsDouble(items[2]);
    Py_DECREF(obj);
}

void get_point_pair(glm::vec3 & a, glm::vec3 & b, PyObject * obj) {
    obj = PySequence_Fast(obj, "not iterable");
    if (!obj || PySequence_Fast_GET_SIZE(obj) != 2) {
        PyErr_Format(PyExc_ValueError, "invalid point pair");
        return;
    }
    PyObject ** items = PySequence_Fast_ITEMS(obj);
    get_point(a, items[0]);
    get_point(b, items[1]);
    Py_DECREF(obj);
}

PyObject * meth_curve(PyObject * self, PyObject * args) {
    glm::vec3 a_pos;
    glm::vec3 a_dir;
    glm::vec3 b_pos;
    glm::vec3 b_dir;
    float t;

    if (!PyArg_ParseTuple(args, "(fff)(fff)(fff)(fff)f", v_xyz(a_pos), v_xyz(a_dir), v_xyz(b_pos), v_xyz(b_dir), &t)) {
        return 0;
    }

    const float t1 = t;
    const float t2 = t1 * t1;
    const float t3 = t2 * t1;
    const float u = t2 * 3.0f - t3 * 2.0f;
    glm::vec3 pos = a_pos * (1.0f - u) + b_pos * u + a_dir * ((t1 + t3 - t2 * 2.0f) * 3.0f) + b_dir * (t3 - t2) * 3.0f;
    return Py_BuildValue("fff", pos.x, pos.y, pos.z);
}

PyObject * meth_path(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"points", "t", "loop", NULL};

    PyObject * points;
    float t;
    int loop = false;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Of|p", keywords, &points, &t, &loop)) {
        return 0;
    }

    points = PySequence_Fast(points, "not iterable");
    if (!points) {
        return 0;
    }

    int num_points = (int)PySequence_Fast_GET_SIZE(points);
    PyObject ** items = PySequence_Fast_ITEMS(points);

    int idx1;
    int idx2;

    if (loop) {
        idx1 = (int)(glm::mod(t, 1.0f) * num_points);
        idx2 = (idx1 + 1) % num_points;
        t = glm::mod(t * num_points, 1.0f);
    } else {
        idx1 = glm::clamp((int)(t * (num_points - 1)), 0, num_points - 2);
        idx2 = idx1 + 1;
        t -= idx1;
    }

    glm::vec3 a_pos;
    glm::vec3 a_dir;
    glm::vec3 b_pos;
    glm::vec3 b_dir;

    get_point_pair(a_pos, a_dir, items[idx1]);
    get_point_pair(b_pos, b_dir, items[idx2]);

    Py_DECREF(points);

    if (PyErr_Occurred()) {
        return 0;
    }

    const float t1 = t;
    const float t2 = t1 * t1;
    const float t3 = t2 * t1;
    const float u = t2 * 3.0f - t3 * 2.0f;
    glm::vec3 pos = a_pos * (1.0f - u) + b_pos * u + a_dir * ((t1 + t3 - t2 * 2.0f) * 3.0f) + b_dir * (t3 - t2) * 3.0f;
    return Py_BuildValue("fff", pos.x, pos.y, pos.z);
}

PyMethodDef module_methods[] = {
    {"curve", (PyCFunction)meth_curve, METH_VARARGS, 0},
    {"path", (PyCFunction)meth_path, METH_VARARGS | METH_KEYWORDS, 0},
    {0},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "bezier", 0, -1, module_methods, 0, 0, 0, 0};

extern "C" PyObject * PyInit_bezier() {
    PyObject * module = PyModule_Create(&module_def);
    return module;
}
