#include <iostream>
#include <Interpreter.hpp>
#include <ScriptError.hpp>

int main(int argc, char** argv)
{
	Interpreter interpreter;
	try
	{
		if(argc >= 2)
		{
			interpreter.loadFile(argv[1]);
			interpreter.interpret();
		}
		else
			interpreter.runPrompt();
	}
	catch(const ScriptError& e)
	{
		std::cerr << "Script error:" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}
