#!/usr/bin/env python3
"""
Generate a simple JSON metadata file for imported assets.
Reads vertical_slice/imported_assets and writes vertical_slice/asset_metadata.json
Run locally: python3 vertical_slice/scripts/generate_asset_metadata.py
"""

import json
from pathlib import Path
from datetime import datetime

IMPORT_DIR = Path(__file__).resolve().parents[1] / "imported_assets"
OUT_FILE = Path(__file__).resolve().parents[1] / "asset_metadata.json"

def gather_assets():
    metadata = {
        "generated_at": datetime.utcnow().isoformat() + "Z",
        "assets": []
    }

    if not IMPORT_DIR.exists():
        print(f"Imported assets folder not found: {IMPORT_DIR}")
        return metadata

    for category in ("models", "textures", "audio", "misc"):
        cat_dir = IMPORT_DIR / category
        if not cat_dir.exists():
            continue
        for item in sorted(cat_dir.iterdir()):
            if not item.is_file():
                continue
            entry = {
                "filename": item.name,
                "category": category,
                "size_bytes": item.stat().st_size,
                "relative_path": str(item.relative_to(Path(__file__).resolve().parents[2])),
            }
            metadata["assets"].append(entry)

    return metadata

def write_metadata(metadata):
    OUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    with OUT_FILE.open("w", encoding="utf-8") as f:
        json.dump(metadata, f, indent=2)
    print(f"Wrote metadata to {OUT_FILE}")

if __name__ == "__main__":
    meta = gather_assets()
    write_metadata(meta)
  
