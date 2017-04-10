# Make a library with all the project sources
# This is useful for building the tests
add_library(GITCY
	BuiltinFunctions.cpp
	BuiltinFunctionsOverloads.cpp
	BuiltinMacros.cpp
	Function.cpp
	Interpreter.cpp
	Macro.cpp
	Null.cpp
	Overload.cpp
	SignatureType.cpp
	ScriptError.cpp
	Utils.cpp
	Value.cpp
	)

# Create the main executable
add_executable(${EXECUTABLE_NAME} main.cpp)

# Link to our binaries
target_link_libraries(${EXECUTABLE_NAME} GITCY)
