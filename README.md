# OmegaInt

[![CodeFactor](https://www.codefactor.io/repository/github/matiasagelvis/omegaint/badge)](https://www.codefactor.io/repository/github/matiasagelvis/omegaint)

Store arbitrarily big integers in C++

This library is intended to add arbitrarily long ints to C++ in a convenient and  versatile way, it is not has tight in memory has others, for every 64 bits in memory one is wasted, but hopefully it compensates in versatility with the ability to make operations between OmegaInt's and other numerical types and std::strings, like 
`OmegaInt(27) - "7"` or 
`OmegaInt(15) + int(14)` and
`OmegaInt(9)^3 == "729"`

The Contents of the OmegaUtils also allows you to swap the contents of two OmegaInts, calculate the GCD and lcm.

For convenience and portability a single header file is located in the folder SingleFile, also a robust makefile made by Wade Fagen-Ulmschneider, Jeffrey Tolar, and Eric Huber at the UIUC is provided.

The main.cpp shows many of the functions of the OmegaInt, and can be compiled into a test program to show many of the features

![logo](logo.png)
