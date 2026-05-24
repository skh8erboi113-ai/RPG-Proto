#!/usr/bin/env python3
"""
Simple asset import helper for the vertical slice.
Scans the vertical_slice/assets folder and copies recognized files
into a structured output directory for packaging.
Run locally: python3 vertical_slice/scripts/import_assets.py
"""

import os
import shutil
from pathlib import Path

SRC_DIR = Path(__file__).resolve().parents[1] / "assets"
OUT_DIR = Path(__file__).resolve().parents[1] / "imported_assets"

# File extensions we care about for the vertical slice
MODEL_EXTS = {".fbx", ".obj", ".gltf"}
TEXTURE_EXTS = {".png", ".jpg", ".jpeg", ".tga"}
AUDIO_EXTS = {".wav", ".ogg", ".mp3"}

def ensure_out():
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    (OUT_DIR / "models").mkdir(exist_ok=True)
    (OUT_DIR / "textures").mkdir(exist_ok=True)
    (OUT_DIR / "audio").mkdir(exist_ok=True)
    (OUT_DIR / "misc").mkdir(exist_ok=True)

def classify_and_copy(src_path: Path):
    ext = src_path.suffix.lower()
    if ext in MODEL_EXTS:
        dest = OUT_DIR / "models" / src_path.name
    elif ext in TEXTURE_EXTS:
        dest = OUT_DIR / "textures" / src_path.name
    elif ext in AUDIO_EXTS:
        dest = OUT_DIR / "audio" / src_path.name
    else:
        dest = OUT_DIR / "misc" / src_path.name

    shutil.copy2(src_path, dest)
    print(f"Copied {src_path} -> {dest}")

def scan_and_import():
    if not SRC_DIR.exists():
        print(f"Source assets folder not found: {SRC_DIR}")
        return 1

    ensure_out()

    for root, _, files in os.walk(SRC_DIR):
        for f in files:
            src = Path(root) / f
            try:
                classify_and_copy(src)
            except Exception as e:
                print(f"Failed to copy {src}: {e}")

    print(f"Import complete. Output: {OUT_DIR}")
    return 0

if __name__ == "__main__":
    raise SystemExit(scan_and_import())
  
