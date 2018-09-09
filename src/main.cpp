#include <iostream>
#include <fstream>
#include <sstream>
#include <Interpreter.hpp>
#include <ScriptError.hpp>


int main(int argc, char** argv)
{
	Interpreter interpreter;
	const std::string standardInputFilename{"-"};
	const std::string prompt{">>> "};
	std::unique_ptr<std::istream> inputStream;
	int i{1};
	bool showPrompt{argc == 1};
	while(showPrompt or i < argc)
	{
		if(argc == 1)
		{
			std::cout << prompt;
			std::string inputString;
			std::getline(std::cin, inputString);
			inputStream = std::make_unique<std::stringstream>(inputString);
			showPrompt = std::cin.good();
		}
		else
		{
			const std::string filename{argv[i]};
			if(filename == standardInputFilename)
				inputStream.reset(&std::cin);
			else
				inputStream = std::make_unique<std::ifstream>(filename);
			++i;
		}
		try
		{
			interpreter.loadFromStream(*inputStream);
			std::cout << interpreter.interpret() << std::endl;
		}
		catch(const ScriptError& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
