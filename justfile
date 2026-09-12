alias b := build

# configure build
build-config:
    cmake -B build

# build executable
build:
    cmake --build build