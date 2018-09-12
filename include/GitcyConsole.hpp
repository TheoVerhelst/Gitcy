#ifndef GITCY_CONSOLE_HPP
#define GITCY_CONSOLE_HPP

#include <vector>
#include <string>
#include <Interpreter.hpp>
#include <Value.hpp>

class GitcyConsole {
	public:
		GitcyConsole(const std::vector<std::string>& filenames);
		void run();

	private:
		Value interpretStream(std::istream& inputStream);

		const std::string _prompt{">>> "};
		const std::string _stinFilename{"-"};
		const std::vector<std::string> _filenames;
		Interpreter _interpreter;
};

#endif // GITCY_CONSOLE_HPP
