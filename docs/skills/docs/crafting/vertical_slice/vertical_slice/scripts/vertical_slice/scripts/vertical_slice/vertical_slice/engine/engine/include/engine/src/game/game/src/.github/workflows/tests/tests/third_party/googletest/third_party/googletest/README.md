# googletest (placeholder)

This folder contains a minimal placeholder CMake configuration so CI and local builds
that expect a `third_party/googletest` directory can succeed.

## Replace with real googletest

To use the real GoogleTest, run:

git submodule add https://github.com/google/googletest.git third_party/googletest
git submodule update --init --recursive

Or fetch and place the googletest sources into this directory.

After adding the real googletest, remove or replace this placeholder CMakeLists.txt.
