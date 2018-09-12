# Make a library with all the project sources
# This is useful for building the tests
add_library(GITCY
	BuiltinFunctions.cpp
	BuiltinFunctionsOverloads.cpp
	BuiltinCallables.cpp
	Callable.cpp
	EvaluationTree.cpp
	Function.cpp
	GitcyConsole.cpp
	Interpreter.cpp
	Null.cpp
	Overload.cpp
	Parser.cpp
	Scope.cpp
	SignatureType.cpp
	ScriptError.cpp
	UserDefinedFunction.cpp
	Utils.cpp
	Value.cpp
	ValueBadGet.cpp
	ValueTypes.cpp
	)

# Create the main executable
add_executable(${EXECUTABLE_NAME} main.cpp)

# Link to our binaries
target_link_libraries(${EXECUTABLE_NAME} GITCY)
