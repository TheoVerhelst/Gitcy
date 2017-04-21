#include <fstream>
#include <memory>
#include <iostream>
#include <Parser.hpp>
#include <ScriptError.hpp>
#include <BuiltinCallables.hpp>
#include <Interpreter.hpp>

Interpreter::Interpreter():
	_prompt{">>> "},
	_globalScope
	{{
		{"print",    std::make_shared<Value>(_functions.print)},
		{"do",       std::make_shared<Value>(_functions.do_)},
		{"<",        std::make_shared<Value>(_functions.lowerThan)},
		{">",        std::make_shared<Value>(_functions.greaterThan)},
		{"<=",       std::make_shared<Value>(_functions.lowerEqual)},
		{">=",       std::make_shared<Value>(_functions.greaterEqual)},
		{"=",        std::make_shared<Value>(_functions.equal)},
		{"is",       std::make_shared<Value>(_functions.equal)},
		{"!=",       std::make_shared<Value>(_functions.notEqual)},
		{"and",      std::make_shared<Value>(_functions.and_)},
		{"or",       std::make_shared<Value>(_functions.or_)},
		{"+",        std::make_shared<Value>(_functions.add)},
		{"-",        std::make_shared<Value>(_functions.substract)},
		{"*",        std::make_shared<Value>(_functions.multiply)},
		{"/",        std::make_shared<Value>(_functions.divide)},
		{"%",        std::make_shared<Value>(_functions.modulo)},
		{"!",        std::make_shared<Value>(_functions.not_)},
		{"true",     std::make_shared<Value>(true)},
		{"false",    std::make_shared<Value>(false)},
		{"null",     std::make_shared<Value>(Null())},
		{"define",   std::make_shared<Value>(Callable(BuiltinCallables::define))},
		{"if",       std::make_shared<Value>(Callable(BuiltinCallables::if_))},
		{"function", std::make_shared<Value>(Callable(BuiltinCallables::defineFunction))},
	}}
{
}

void Interpreter::loadFile(const std::string& filename)
{
	std::ifstream stream{filename};
	const std::string fileContent{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
	_evaluationTree = Parser::constructTree(fileContent);
}

Value Interpreter::interpret()
{
	return BuiltinCallables::evaluate(_evaluationTree, _globalScope);
}

void Interpreter::runPrompt()
{
	while(true)
	{
		std::cout << _prompt;
		std::string input;
		std::getline(std::cin, input);
		_evaluationTree = Parser::constructTree(input);
		try
		{
			std::cout << interpret() << std::endl;
		}
		catch(const ScriptError& e)
		{
			std::cerr << "Script error: " << e.what() << std::endl;
		}
	}
}
