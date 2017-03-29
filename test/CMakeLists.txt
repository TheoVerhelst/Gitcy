# Find the unit test framework library
find_package(Boost 1.57 COMPONENTS unit_test_framework REQUIRED)

# This define is needed by the Boost unit test framework
add_definitions(-DBOOST_TEST_DYN_LINK)

# All test source files
set(TEST_SOURCES
	DataTest.cpp
	NullTest.cpp
	main.cpp
	)

# Create the main test executable
add_executable(${EXECUTABLE_NAME}Test ${TEST_SOURCES})

# Link the executable with our binaries and boost library
target_link_libraries(${EXECUTABLE_NAME}Test GITCY ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
