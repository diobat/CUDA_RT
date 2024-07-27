cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(CUDA_RT VERSION 0.1.0 LANGUAGES CXX CUDA)

enable_language(CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Set policies
cmake_policy(SET CMP0135 NEW) # Link directories must be absolute

# Add header files
file(GLOB_RECURSE HEADER_FILES 
  ${CMAKE_SOURCE_DIR}/src/*.hpp
  ${CMAKE_SOURCE_DIR}/src/*.cuh
)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.cu
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
)

# Fetch dependencies remotely
include(FetchContent) 


########### DEPENDENCIES ###########

####################################
 