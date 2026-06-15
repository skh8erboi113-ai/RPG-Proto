import os
import json
import sys

def validate_json(file_path):
    if not os.path.exists(file_path):
        print(f"ERROR: Missing JSON file: {file_path}")
        return False
    try:
        with open(file_path, 'r') as f:
            json.load(f)
        print(f"OK: {file_path} is valid JSON.")
        return True
    except json.JSONDecodeError as e:
        print(f"ERROR: Invalid JSON in {file_path}: {e}")
        return False

def check_directory(dir_path):
    if os.path.isdir(dir_path):
        print(f"OK: Directory exists: {dir_path}")
        return True
    else:
        print(f"ERROR: Missing directory: {dir_path}")
        return False

def main():
    success = True

    # Critical Directories
    dirs_to_check = [
        "engine",
        "game",
        "docs",
        "scripts",
        "tests",
        "shaders"
    ]

    print("--- Checking Directories ---")
    for d in dirs_to_check:
        if not check_directory(d):
            success = False

    # Critical Files
    files_to_check = [
        "CMakeLists.txt",
        "README.md",
        "MANIFEST.json",
        "docs/DESIGN_FULL.md"
    ]

    print("\n--- Checking Critical Files ---")
    for f in files_to_check:
        if os.path.exists(f):
            print(f"OK: File exists: {f}")
        else:
            print(f"ERROR: Missing file: {f}")
            success = False

    # JSON Validation
    json_files = [
        "docs/crafting/FullRecipes.json",
        "docs/skills/FullSkillTrees.json",
        "docs/vertical_slice/manifest.json"
    ]

    print("\n--- Validating JSON Files ---")
    for jf in json_files:
        if not validate_json(jf):
            success = False

    if success:
        print("\nSUCCESS: Repository validation passed.")
        sys.exit(0)
    else:
        print("\nFAILURE: Repository validation failed.")
        sys.exit(1)

if __name__ == "__main__":
    main()
