cmake_minimum_required(VERSION 3.10)
project(MySystemCProject)

# Specify the path to the SystemC installation directory
set(SystemC_DIR )

# Find the SystemC package
find_package(SystemC REQUIRED)

# Include directories for SystemC
include_directories(${SystemC_INCLUDE_DIRS})

# Add your source files here
add_executable(MySystemCProject main.cpp)

# Link SystemC libraries
target_link_libraries(MySystemCProject ${SystemC_LIBRARIES})
