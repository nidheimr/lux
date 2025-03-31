# Lux

## Overview

Lux is a simple library that does the following:
- allows the creation and management of a win32 window
- creates and manages a 3.3 core opengl context
- manually loads all opengl functions from 1.0 to 3.3

It was written for educational purposes and is likely not very efficient.

## Building

This project uses CMake.

Assuming you have CMake installed and some form of windows C compiler (such as MSVC), you can run the following commands inside the project directory:
1. `cmake -S . -B build`
2. `cmake --build build`

The library will be placed inside `./bin/`.