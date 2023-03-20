# CMakeList.txt : CMake project for ImageProcessing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ImageProcessing")

# Add source to this project's executable.
add_executable (ImageProcessing  "src/main.cpp" "src/header.h")

# TODO: Add tests and install targets if needed.
