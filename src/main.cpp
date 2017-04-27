#include <iostream>
#include <fstream>
#include <Interpreter.hpp>
#include <ScriptError.hpp>


int main(int argc, char** argv)
{
	Interpreter interpreter;
	constexpr std::string standardInputFilename{"-"};
	try
	{
		if(argc == 1)
			interpreter.runPrompt();
		else
		{
			for(int i{1}; i < argc; ++i)
			{
				const std::string filename{argv[i]};
				if(filename == standardInputFilename)
					interpreter.loadFromStream(std::cin);
				else
				{
					std::ifstream stream{filename};
					interpreter.loadFromStream(stream);
				}
				interpreter.interpret();
			}
		}
	}
	catch(const ScriptError& e)
	{
		std::cerr << "Script error:" << std::endl;
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
