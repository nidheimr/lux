# Lux

## Overview

Lux is a simple windowing and rendering library.

It was written for educational purposes and is likely not very efficient.

## Building

This project uses CMake. The only supported platforms for this project are: Linux (Wayland).

Assuming you have CMake and a C compiler, you can run the following commands inside the project directory:
1. `cmake -S . -B build`
2. `cmake --build build`

The library will be placed inside `./bin/`.

If you want to build the test executable, append `-D BUILD_TEST_EXECUTABLE=1` to the first CMake command.
