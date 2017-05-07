cmake_minimum_required(VERSION 2.8)
project(Gitcy)

set(EXECUTABLE_NAME "Gitcy")

# Add an option to build the tests
option(BUILD_TESTS "TRUE to build the tests" FALSE)

# Set the include directory of the project
include_directories("${CMAKE_SOURCE_DIR}/include")

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Winline -Wunreachable-code -Wmissing-declarations")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Place the executable files in the root directory instead of in src
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)

# Build the tests if requested
if(BUILD_TESTS)
	add_subdirectory(test)
endif()
