#include <GitcyConsole.hpp>


int main(int argc, char** argv)
{
	GitcyConsole console{std::vector<std::string>(argv + 1, argv + argc)};
	console.run();
}
