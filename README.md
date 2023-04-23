# cvarint - A C Extension for Python

After having implemented protobuf varint with python [here](https://github.com/easmar89/protobuf-varint), it was time to step up the challenge and implement a C extension for Python that implements varint encoding and decoding. The primary purpose of this exercise is to provide a learning opportunity for understanding and exploring various aspects of software development, such as:

- Reading and understanding large codebases (CPython)
- Building and working with C extensions for Python
- Enhancing performance of a Python program through C extensions, as indicated in the results below.

## Overview

The `cvarint` module provides two primary functions:

- `cvarint.encode(n: int) -> bytes`: Encodes a given unsigned integer n into a variable-length byte sequence.
- `cvarint.decode(b: bytes) -> int`: Decodes a given byte sequence b back into an unsigned integer.

These functions are implemented in C to provide better performance compared to their native Python counterparts.

## Sample output:

```txt
Running speed test...
Executed 1,000,000 random tests

Python:	  3289ns per case (3.289s total)
C:	      952ns per case (0.952s total)
```

## References:

- CPython: https://github.com/python/cpython/tree/ee821dcd3961efc47262322848267fe398faa4e4
- Extending Python with C or C++: https://docs.python.org/3/extending/extending.html
