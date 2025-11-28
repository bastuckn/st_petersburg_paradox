cmake_minimum_required(VERSION 3.14)
project(StPetersburgSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project headers
include_directories(include)

# External headers
include_directories(external/progressbar/include)

# Add Matplot++ as subdirectory
add_subdirectory(external/matplotplusplus)

# Source files
file(GLOB SRC_FILES src/*.cpp)

# Executable
add_executable(StPetersburgSim ${SRC_FILES})

# Link Matplot++ library
target_link_libraries(StPetersburgSim PRIVATE matplot)
