rm -rf build

cmake -S . -B build

cmake --build build --config Release --verbose --parallel 4

cd build

./lc3tests

cd ..