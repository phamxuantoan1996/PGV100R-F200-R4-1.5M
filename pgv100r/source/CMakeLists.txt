cmake_minimum_required(VERSION 3.10)
project(PGV100R LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directory
include_directories(${PROJECT_SOURCE_DIR}/../include)

# Source files
set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/pgv100r.cpp
)

# Create static library (.a)
add_library(pgv100r STATIC ${SRC_FILES})

# # Optional: add pthread if needed
# find_package(Threads REQUIRED)
# target_link_libraries(pgv100r PUBLIC Threads::Threads)

# # Output directory for compiled library
# set_target_properties(pgv100r PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../build
# )
