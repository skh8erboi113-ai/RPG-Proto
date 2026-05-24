#!/usr/bin/env bash
# Export placeholder assets into the vertical slice assets folder.
# Use locally to create minimal placeholder files so CI and packaging succeed.
# Run: bash vertical_slice/export_placeholder_assets.sh

set -euo pipefail
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ASSETS_DIR="$ROOT_DIR/assets"

mkdir -p "$ASSETS_DIR"
touch "$ASSETS_DIR/placeholder_character.fbx"
touch "$ASSETS_DIR/placeholder_env_block.fbx"
touch "$ASSETS_DIR/placeholder_horse.fbx"
mkdir -p "$ASSETS_DIR/placeholder_textures"
for i in 1 2 3; do
  png="$ASSETS_DIR/placeholder_textures/placeholder_${i}.png"
  if [ ! -f "$png" ]; then
    # create a tiny valid PNG if imagemagick is available, otherwise an empty file
    if command -v convert >/dev/null 2>&1; then
      convert -size 4x4 xc:gray "$png"
    else
      touch "$png"
    fi
  fi
done

echo "Exported placeholder assets to: $ASSETS_DIR"
ls -la "$ASSETS_DIR"
