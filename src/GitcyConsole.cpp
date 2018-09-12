#include <iostream>
#include <fstream>
#include <sstream>
#include <ScriptError.hpp>
#include <Null.hpp>
#include <GitcyConsole.hpp>

GitcyConsole::GitcyConsole(const std::vector<std::string>& filenames):
	_filenames{filenames}
{
}

void GitcyConsole::run()
{
	for(const auto& filename : _filenames)
	{
		if(filename == _stinFilename)
			interpretStream(std::cin);
		else
		{
			std::ifstream fileStream{filename};
			interpretStream(fileStream);
		}
	}

	if(_filenames.empty())
	{
		while(std::cin.good())
		{
			std::cout << _prompt;
			std::string inputString;
			std::getline(std::cin, inputString);
			std::stringstream stringStream{inputString};
			std::cout << interpretStream(stringStream) << std::endl;
		}
	}
}

Value GitcyConsole::interpretStream(std::istream& inputStream)
{
	try
	{
		_interpreter.loadFromStream(inputStream);
		return _interpreter.interpret();
	}
	catch(const ScriptError& e)
	{
		std::cerr << e.what() << std::endl;
		return Null();
	}
}
