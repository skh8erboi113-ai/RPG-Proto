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

# Ensure placeholder source assets exist (fbx/png placeholders + the
# simple_box.obj the Renderer loads at runtime)
if [ ! -d "$ASSETS_DIR" ]; then
  echo "Assets folder not found. Exporting placeholder assets..."
  bash "$ROOT_DIR/scripts/export_placeholder_assets.sh"
fi
if [ ! -f "$ASSETS_DIR/simple_box.obj" ]; then
  echo "simple_box.obj not found. Generating placeholder mesh..."
  python3 "$ROOT_DIR/scripts/generate_placeholder_mesh.py"
fi

# Ensure import step has run
if [ ! -d "$IMPORT_DIR" ]; then
  echo "Imported assets not found. Running import script..."
  python3 "$ROOT_DIR/scripts/import_assets.py"
fi

# Generate metadata
python3 "$ROOT_DIR/scripts/generate_asset_metadata.py"

# Prepare package
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR/assets"
mkdir -p "$OUT_DIR/scripts"
mkdir -p "$OUT_DIR/docs"

# Copy imported assets
cp -r "$IMPORT_DIR"/* "$OUT_DIR/assets/" || true

# Copy scripts and manifest
cp "$ROOT_DIR/manifest.json" "$OUT_DIR/"
cp -r "$ROOT_DIR/scripts" "$OUT_DIR/"

# Copy vertical slice docs if present
if [ -d "$ROOT_DIR/docs/vertical_slice" ]; then
  cp -r "$ROOT_DIR/docs/vertical_slice" "$OUT_DIR/docs/"
fi

echo "Packaging complete. Package located at: $OUT_DIR"
