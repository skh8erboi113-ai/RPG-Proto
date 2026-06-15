# Modern Gothic RPG — Prototype Repository

## Status
Design and engineering blueprint with vertical slice artifacts and prototype code.

## Quick Project Overview
This repository contains a modular C++ engine skeleton and design documentation for a Modern Gothic RPG.

### Key Components
- **Engine Skeleton**: Modular C++ core with character, renderer (bgfx), camera, and world streaming systems.
- **Game Application**: A prototype entry point demonstrating the engine's lifecycle.
- **Build System**: Self-contained CMake build using `FetchContent` for dependencies.
- **Design Docs**: Full game design, skill trees, loot tables, and crafting recipes in `docs/`.
- **Scripts**: Asset import and metadata generation helpers in `scripts/`.

## Prerequisites
- **CMake**: 3.16 or newer
- **C++20 Toolchain**: GCC 10+, Clang 10+, or MSVC 2019+
- **System Libraries (Linux)**: `libglfw3-dev`, `libgl1-mesa-dev`, `libglu1-mesa-dev`, and X11 development headers.

## Building and Running

### Build
```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run Game
```bash
./build/game/game
```

### Run Tests
```bash
# Use xvfb-run if in a headless environment
xvfb-run ./build/tests/test_stats
```

## Repository Manifest
For a machine-readable summary of the repository contents, see [MANIFEST.json](MANIFEST.json).

## Validation
To validate the repository structure and data files, run:
```bash
python3 scripts/validate_repo.py
```

## Project Structure
- `engine/`: Core engine library source and includes.
- `game/`: Main game application source.
- `tests/`: Unit tests using GoogleTest.
- `docs/`: Design documentation and JSON data.
- `scripts/`: Helper scripts for assets and builds.
- `shaders/`: bgfx shader source files.

## Prototype Features
The current version demonstrates the following core RPG systems:
- **Character Controller**: 3D movement and positioning.
- **Stats & Progression**: XP-based leveling (.08^n$ curve) and angelic/demonic alignment.
- **Skill System**: JSON-based skill trees with dynamic scaling.
- **Inventory & Crafting**: Item management and material-based crafting recipes.
- **Wanted System**: Crime reporting and wanted levels tracked per city.
- **Graphics & World**: Modern bgfx renderer with world streaming and player-following camera.
