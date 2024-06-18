# Fast plugins

This repository contains a collection of NVGT plugins for maximizing performance. These plugins include:

- [] Plugin fast:
    - [x] SIMD-accelerated elementary functions to replace the built-in ones, in namespace fast, as well as SIMD-accelerated blend and approximations of `sin`, `cos`, `atan2`, and `atan` when completely valid input is used and you don't absolutely need libc-level compliance (credit goes to Jeroen van der Zijp)
    - [] GPU/OpenCL offloading
- [ ] Physics

More will definitely come in the future -- feel free to recommend more and contribute! These libraries should build itself pretty much out of the box, though you will need an internet connection.

## License

All code in this repository is placed into the public domain. You are free to do what you wish with this software. Attribution is of course encouraged, though I will not try to legally compel it.