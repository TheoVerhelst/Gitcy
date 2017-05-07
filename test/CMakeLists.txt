# Find the unit test framework library
find_package(Boost 1.57 COMPONENTS unit_test_framework REQUIRED)

# This define is needed by the Boost unit test framework
add_definitions(-DBOOST_TEST_DYN_LINK)

# All test source files
set(TEST_SOURCES
	BuiltinFunctionsOverloadsTest.cpp
	BuiltinCallablesTest.cpp
	DataTest.cpp
	FunctionTest.cpp
	NullTest.cpp
	SignatureTypeTest.cpp
	UtilsTest.cpp
	main.cpp
)

set(TEST_EXECUTABLE_NAME "${EXECUTABLE_NAME}Test")

# Create the main test executable
add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCES})

# Link the executable with our binaries and boost library
target_link_libraries(${TEST_EXECUTABLE_NAME} GITCY ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# Execute tests after the build
add_custom_command(TARGET ${TEST_EXECUTABLE_NAME} POST_BUILD
    COMMAND "${CMAKE_BINARY_DIR}/${TEST_EXECUTABLE_NAME}"
)
