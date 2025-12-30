[![progress-banner](https://backend.codecrafters.io/progress/shell/4fef01ae-4c16-4b3a-90a0-f6e32606126f)](https://app.codecrafters.io/users/codecrafters-bot?r=2qF)

# CodeCrafters Shell (C++)

Build a minimal POSIX-like shell in C++ with a REPL that parses commands, handles builtins, and runs external programs. This repository is the implementation workspace for the CodeCrafters "Build Your Own Shell" challenge.

## What this project does

This project implements a simple interactive shell:

- Reads commands via a REPL prompt (`$ `)
- Supports built-in commands: `echo`, `exit`, `type`, `pwd`, `cd`
- Resolves executables using the `PATH` environment variable
- Runs external programs with arguments

Core entry point: see `src/main.cpp`.

## Why this project is useful

- Learn shell internals: parsing, builtins, PATH resolution, process execution
- Practice modern C++23 and standard library facilities
- Ready-to-run local setup with CMake and vcpkg

## Getting started

### Prerequisites

- CMake >= 3.13
- A C++ compiler with C++23 support (e.g., GCC 13+, Clang 16+)
- vcpkg installed and `VCPKG_ROOT` set (used by this project)
- Linux or macOS recommended

Optional dependencies:

- `readline` (linked via vcpkg/toolchain)

### Install dependencies

- vcpkg manifest is in `vcpkg.json`
- Configuration overrides in `vcpkg-configuration.json`

Ensure `VCPKG_ROOT` is set in your environment.

### Build

You can use the helper script for local builds:

- `./your_program.sh`

This script:

- Configures the CMake build using the vcpkg toolchain
- Builds the `shell` executable into `build/`
- Executes `build/shell`

Alternatively, manual steps:

- `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake`
- `cmake --build build`
- `./build/shell`

Project configuration: see `CMakeLists.txt`.

### Usage

Run the shell:

- `./build/shell`

Examples:

- `echo hello world` → prints `hello world`
- `pwd` → prints current directory
- `cd /tmp` → changes directory
- `type echo` → reports builtin/external resolution
- `ls -la` → runs external program from `PATH`
- `exit` → exits the shell

Notes:

- Commands are split on spaces (basic parsing). Quoting and redirection are not implemented.
- External programs are discovered by scanning directories in `$PATH` and checking executability.

## Where to get help

- Challenge overview: link from the banner in the original scaffold or visit codecrafters.io
- Code structure: `src/main.cpp`, `your_program.sh`, `CMakeLists.txt`
- Open an issue in this repository for questions and support

## Who maintains and contributes

- Maintainer: you (the repository owner)
- Contributions: pull requests are welcome
  - Keep changes focused and include a clear description
  - Add tests or usage examples where applicable

## Project structure

- `src/main.cpp` — shell REPL and builtin/external command handling
- `your_program.sh` — local build/run helper
- `CMakeLists.txt` — CMake configuration (C++23, readline link)
- `vcpkg.json` — dependencies manifest
- `vcpkg-configuration.json` — vcpkg configuration
- `codecrafters.yml` — challenge integration config

## License

Refer to the repository's `LICENSE` file if present.
