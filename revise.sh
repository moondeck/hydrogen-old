#!/bin/bash
make clean
make kernel_x86
rm *.o
qemu-system-i386 -kernel hydrogen -m size=32M -serial stdio
rm hydrogen
