conan profile detect --force
conan install . --output-folder=./build_for_vs2022 --build=missing -s build_type=Debug
cmake --preset conan-default

cd ./build_for_vs2022
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build_for_vs2022 . --config Debug




