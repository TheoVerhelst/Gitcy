set(SOURCE_FILES
	Data.cpp
	Function.cpp
	Functions.cpp
	Interpreter.cpp
	Overload.cpp
	SignatureType.cpp
	ScriptError.cpp
	main.cpp
	)

#Create the main executable
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

#Link external librairies
target_link_libraries(${EXECUTABLE_NAME} ${EXTERNAL_LIBRARIES})
