#!/bin/bash
clang --target=wasm32 -O3 -nostdlib -fno-builtin-memcpy -Wl,--no-entry -Wl,--export-all -o gol.wasm gol.c
