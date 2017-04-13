#include <iostream>
#include <Interpreter.hpp>
#include <ScriptError.hpp>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cerr << "Need script filename as argument" << std::endl;
		return 1;
	}
	
	Interpreter i(argv[1]);
	try
	{
		i.interpret();
	}
	catch(const ScriptError& e)
	{
		std::cerr << "Script error:" << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
