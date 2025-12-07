default:
    echo "enter a valid argument"

build:
    rm -rf build
    mkdir build
    cmake -S . -B build
    cmake --build build
