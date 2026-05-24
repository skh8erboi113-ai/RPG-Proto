Modern Gothic RPG — Prototype Repository
Status: Design and engineering blueprint with vertical slice artifacts and prototype code.
Scope: Production‑ready design docs, skill/loot/recipe JSON, vertical slice manifest and scripts, C++ skeleton modules, unit tests, and asset pipeline helpers.

Quick Project Overview
What this repo contains

Design docs: full game design, mission scripts, skill trees, loot tables, crafting recipes.

Vertical slice: Ashbourne prototype manifest, asset placeholders, build and import scripts.

Engine skeleton: modular C++ game core with character, stats, skills, inventory, crafting, save, and wanted systems.

Build system: CMake files for client, optional server, and unit tests.

Tools: Python asset import and metadata generators.

Tests: GoogleTest unit test examples for core systems.

Intended use

Start a vertical slice implementation.

Hand off to engineers, designers, and artists.

Iterate into a full production pipeline.

Prerequisites
Required

CMake 3.16 or newer

C++17 toolchain (GCC, Clang, or MSVC)

Python 3.8+ for asset scripts

nlohmann/json library (included under third_party or via package manager)

GoogleTest for unit tests (included under third_party or via package manager)
