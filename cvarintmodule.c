#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdint.h>

static PyObject *cvarint_encode(PyObject *self, PyObject *args) {
    uint64_t num;
    uint8_t bytes[10] = {0};
    int i = 0;

    if(!PyArg_ParseTuple(args, "K", &num)){
        return NULL;
    }

    while (num > 0) {
        uint8_t least_significant_7_bits = num & 0x7f;
        bytes[i] = least_significant_7_bits | 0x80;
        num >>= 7;
        i++;
    }

    bytes[i - 1] &= 0x7f; 

    return PyBytes_FromStringAndSize((char *)bytes, i);
}

static PyObject *cvarint_decode(PyObject *self, PyObject *args) {
    uint8_t *arr;
    Py_ssize_t length;
    uint64_t num = 0;
    uint64_t byte_value = 0;
    int shift = 0;

    if (!PyArg_ParseTuple(args, "y#", &arr, &length)) {
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        byte_value = arr[i] & 0x7f;
        num |= (byte_value << shift);
        shift += 7;

        if ((arr[i] & 0x80) == 0) break;
    }

    return PyLong_FromUnsignedLongLong(num);
}


static PyMethodDef CVarintMethods[] = {
    {"encode", cvarint_encode, METH_VARARGS, "Encode an integer as varint."},
    {"decode", cvarint_decode, METH_VARARGS,
     "Decode varint bytes to an integer."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cvarintmodule = {
    PyModuleDef_HEAD_INIT, "cvarint",
    "A C implementation of protobuf varint encoding", -1, CVarintMethods};

PyMODINIT_FUNC PyInit_cvarint(void) { return PyModule_Create(&cvarintmodule); }
