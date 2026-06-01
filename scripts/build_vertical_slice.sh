#!/usr/bin/env bash
# Simple vertical slice build helper
# Run locally: bash scripts/build_vertical_slice.sh

set -euo pipefail
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ASSETS_DIR="$ROOT_DIR/assets"
IMPORT_DIR="$ROOT_DIR/imported_assets"
OUT_DIR="$ROOT_DIR/vertical_slice_package"

echo "Root: $ROOT_DIR"
echo "Assets: $ASSETS_DIR"
echo "Import dir: $IMPORT_DIR"
echo "Output: $OUT_DIR"

# Build engine and game
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Ensure import step has run (if assets dir exists)
if [ -d "$ASSETS_DIR" ]; then
  echo "Assets found. Running import script..."
  python3 "$ROOT_DIR/scripts/import_assets.py"
fi

# Prepare package
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR/bin"
mkdir -p "$OUT_DIR/docs"

# Copy binaries
cp build/game/game "$OUT_DIR/bin/"
cp -r build/game/shaders "$OUT_DIR/bin/"

# Copy docs
cp -r "$ROOT_DIR/docs"/* "$OUT_DIR/docs/"

echo "Packaging complete. Package located at: $OUT_DIR"
