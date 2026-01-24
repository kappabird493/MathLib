# MathLib

MathLib is a lightweight, header-only C++ math library providing essential vector and matrix types commonly used in graph­ics, physics, and game development.  
It currently supports:

- `Vec2`, `Vec3`, `Vec4`
- `Mat2`, `Mat3`, `Mat4`

This library is suitable for students, hobby projects, and small engines that need simple and fast math without dependencies.

---

## Features

- Header-only (just include it and use)
- No external dependencies
- Basic arithmetic operators:
  - `+`, `-`, `*`, `/`
- Matrix × matrix multiplication
- Matrix × vector multiplication
- Scalar operations
- Determinant, transpose
- Identity/zero/ones generators
- Printable debug output

---

## Directory Structure

MathLib/
├─ include/
│ └─ math/
│ ├─ Vec2.hpp
│ ├─ Vec3.hpp
│ ├─ Vec4.hpp
│ ├─ Mat2.hpp
│ ├─ Mat3.hpp
│ └─ Mat4.hpp
├─ example/
│ └─ main.cpp
└─ CMakeLists.txt
