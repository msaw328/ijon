IJON (pronounced like "e-yon") is a symmetric block cipher with 128 bits of block and key size. The name of the cipher is not an acronym.
Instead, it references Ijon Tichy, a protagonist of many novels by polish Sci-Fi author Stanisław Lem.
The name was chosen to celebrate the 100th anniversary of author's birth (Stanisław Lem was born in 1921).

The cipher is meant to serve as an example application of the sponge construction in a key expansion algorithm.
Its design and implementation were the topic of my thesis at AGH University of Science and Technology in Kraków, Poland.
The thesis also resulted in publication of an article titled "A Sponge-Based Key Expansion Scheme for Modern Block Ciphers".

----

This repository contains a reference implementation of IJON written in C along with accompanying scripts and examples. It has been tested on Linux, though it may be possible to build it on other operating systems as well.

CMake is required to build this software. Suggested steps to build:

$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=<build type> ..
$ make

To build examples run "make examples" as well. Not all examples are expected to compile on all operating systems, consult the source code to look for OS-specific features.

Four CMake build types are supported:
Debug           - not optimized, debug symbols present
RelWithDebInfo  - O2 optimized, debug symbols present
Release         - O3 optimized, no debug info
MinSizeRel      - Os space optimized, no debug info

To additionally link with "-nostdlib" pass the "-DIJON_NO_STD=1" option to the cmake command.

Result of building is a "libijon.so" shared library. Functions exposed from the library can be found in the ijon/ijon.h header in the include directory.
