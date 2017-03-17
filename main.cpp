#include "Interpreter.hpp"

int main(int argc, char** argv)
{
	Interpreter i(argv[1]);
	i.interpret();
}
