cmake_minimum_required(VERSION 3.30)

# Set project name
project(MyImageExporter)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the stb_image_write header-only library
include_directories(include)

# Add the executable
add_executable(MyImageExporter src/main.cpp)

# Optionally, if you want to make stb an "importable" library (e.g., with target)
add_library(stb_image_write INTERFACE)
target_include_directories(stb_image_write INTERFACE /include)

# Link the library to the executable
target_link_libraries(MyImageExporter PRIVATE stb_image_write)
