default:
    echo "enter a valid argument"

build:
    rm -rf build
    cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cmake --build build

run:
    ./build/NFA_Traversal_Steps
