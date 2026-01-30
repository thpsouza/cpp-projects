cmake_minimum_required(VERSION 3.15)
project(LinearAlgebra CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fcolor-diagnostics -fansi-escape-codes")

# Set optimization flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()

# Add source files
set(SOURCES
    src/Shape.cpp
)

# Add header-only library
add_library(LinAlg INTERFACE)

# Include directories
target_include_directories(LinAlg 
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add implementation library (for non-header sources)
add_library(LinAlg_impl ${SOURCES})
target_include_directories(LinAlg_impl 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Expose both libraries
set(LinearAlgebra_LIBRARIES LinAlg LinAlg_impl PARENT_SCOPE)
set(LinearAlgebra_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)


# Main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE LinearAlgebra)
target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)