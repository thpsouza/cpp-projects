cmake_minimum_required(VERSION 3.15)
project(CustomNeuralNetwork CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fcolor-diagnostics -fansi-escape-codes")

# Set optimization flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()

# Source files
set(FRAMEWORK_SOURCES
    src/NN.cpp
    src/ActivationFunctions/BaseActivationFunction.cpp
    src/ActivationFunctions/ReLUActivationFunction.cpp
    src/ActivationFunctions/SigmoidActivationFunction.cpp
    src/ActivationFunctions/TanhActivationFunction.cpp
    src/LossFunctions/BaseLossFunction.cpp
    src/LossFunctions/MeanSquaredErrorLossFunction.cpp
    src/Optimizers/BaseOptimizer.cpp
    src/Optimizers/StochasticGDOptimizer.cpp
)

# Get LinearAlgebra from parent
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../")
include(LinearAlgebra/CMakeLists.txt)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LinearAlgebra_INCLUDE_DIRS})

# Create library
add_library(framework ${FRAMEWORK_SOURCES})
target_include_directories(framework 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${LinearAlgebra_INCLUDE_DIRS}
)
target_link_libraries(framework PUBLIC LinAlg LinAlg_impl)

# Executable
add_executable(main main.cpp)
target_include_directories(main 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LinearAlgebra_INCLUDE_DIRS}
)
target_link_libraries(main PRIVATE framework LinAlg LinAlg_impl)