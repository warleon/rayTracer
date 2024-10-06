cmake_minimum_required(VERSION 3.30)

# Set project name
project(rayTracer CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
message("CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

# Include FetchContent module for downloading GLM
include(FetchContent)

# Download GLM from GitHub
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1  # Specify GLM version or commit
)

# Add the stb_image_write header-only library
include_directories(include)

# Make GLM available
FetchContent_MakeAvailable(glm)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)


# Automatically find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(rayTracer ${SOURCES})

# Optionally, if you want to make stb an "importable" library (e.g., with target)
add_library(stb_image_write INTERFACE)
target_include_directories(stb_image_write INTERFACE /include)

# Link the library to the executable
target_link_libraries(rayTracer PRIVATE stb_image_write)
target_link_libraries(rayTracer PRIVATE glm)

install(TARGETS rayTracer DESTINATION dist)
