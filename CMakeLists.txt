cmake_minimum_required(VERSION 2.8)
project(Functional)

set(EXECUTABLE_NAME "Functional")

#Set path to Find scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -pedantic-errors -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Winline -Wunreachable-code -Wmissing-declarations -ftemplate-backtrace-limit=0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(SOURCE_FILES Data.cpp Function.cpp main.cpp Functions.cpp Interpreter.cpp)

#Create the main executable
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

