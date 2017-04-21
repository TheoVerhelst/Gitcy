#include <fstream>
#include <memory>
#include <Parser.hpp>
#include <BuiltinCallables.hpp>
#include <Interpreter.hpp>

Interpreter::Interpreter(const std::string& filename):
	_filename(filename),
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
	loadScript();
}

void Interpreter::loadScript()
{
	std::ifstream stream{_filename};
	const std::string fileContent{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
	_evaluationTree = Parser::constructTree(fileContent);
}

void Interpreter::interpret()
{
	BuiltinCallables::evaluate(_evaluationTree, _globalScope);
}
