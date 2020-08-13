# wasm-gol

Simple Game of Life implementation in C, compiled to WebAssembly using LLVM (and not Emscripten).

## Build command

Based on this [excellent article](https://surma.dev/things/c-to-webassembly/).

```bash
clang \
	--target=wasm32 \ # Only available in recent LLVM versions
	-O3 \ # Agressive optimizations
	-nostdlib \ # Do not link against a standard library
	-fno-builtin-memcpy \ # Do not replace manual copying with calls to memcpy
	-Wl,--no-entry \ # Do not search for entry point
	-Wl,--export-all \ # Export all symbols
	-o gol.wasm \ # Output file
	gol.c # Input file
```
