
@echo off
setlocal

set "folderToCheck=./build_for_vs2022"

rmdir /s /q "%folderToCheck%" 2>nul

rem check
if exist "%folderToCheck%" (
    rem "%folderToCheck%" still exist, goto :eof
    
    pause
    goto :eof
) else (
    echo "%folderToCheck%" not exist
)

conan profile detect --force
conan install . --output-folder=./build_for_vs2022  --profile=default --build=missing -s build_type=Debug -s build_type=Release
cmake --preset conan-default

cd ./build_for_vs2022
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build . --config Debug --config Release

pause


