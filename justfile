alias b := build

# configure build
build-config:
    cmake -S . -B build -G Ninja

# build executable
build:
    cmake --build build