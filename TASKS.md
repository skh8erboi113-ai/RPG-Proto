# FOLLOW-UP TASKS — Modern Gothic RPG

## Priority Tasks
1. **Fix Remaining Build Warnings**: Address LTO and serial compilation warnings in CMake. (Effort: Small)
2. **Expand Test Coverage**: Add tests for WorldStreamer and Renderer. (Effort: Medium)
3. **Integrated Asset Pipeline**: Link `scripts/import_assets.py` with the CMake build process. (Effort: Medium)

## Reversibility / Rollback
To revert curation changes:
- `git checkout HEAD -- README.md engine/src/CharacterController.cpp engine/src/Engine.cpp tests/test_stats.cpp`
- `rm MANIFEST.json scripts/validate_repo.py CURATION_REPORT.md TASKS.md`
