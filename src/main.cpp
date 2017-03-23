#include <iostream>
#include <Interpreter.hpp>
#include <ScriptError.hpp>

int main(int /* argc */, char** argv)
{
	Interpreter i(argv[1]);
	try
	{
		i.interpret();
	}
	catch(const ScriptError& e)
	{
		std::cerr << "Script error:" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}
