cmake_minimum_required(VERSION 3.20)
project(CPP_Projects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

# Note: Currently using direct clang++ compilation via build.ps1
# This CMakeLists.txt is for future migration

# LinearAlgebra Library
add_subdirectory(LinearAlgebra)

# CustomNeuralNetwork
add_subdirectory(MachineLearning/CustomNeuralNetwork)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE LinearAlgebra CustomNeuralNetwork)
target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/LinearAlgebra/include
    ${CMAKE_SOURCE_DIR}/MachineLearning/CustomNeuralNetwork/include
)