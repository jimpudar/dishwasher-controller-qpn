# BSP

The Board Support Package (BSP) in QP is the abstraction layer between the
state machine and the hardware.

`include/bsp.h` remains portable between targets, but you can have multiple 
implementations of this interface in this directory. You can use multiple
PlatformIO environments with `build_src_filter` to choose which implementation
is built and linked against for each board.
