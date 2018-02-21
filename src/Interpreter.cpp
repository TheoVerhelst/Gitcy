#include <memory>
#include <iostream>
#include <Null.hpp>
#include <ScriptError.hpp>
#include <BuiltinCallables.hpp>
#include <Interpreter.hpp>

Interpreter::Interpreter():
	_globalScope
	{{
		{"print",    std::make_shared<Value>(BuiltinFunctions::print)},
		{"do",       std::make_shared<Value>(BuiltinFunctions::do_)},
		{"<",        std::make_shared<Value>(BuiltinFunctions::lowerThan)},
		{">",        std::make_shared<Value>(BuiltinFunctions::greaterThan)},
		{"<=",       std::make_shared<Value>(BuiltinFunctions::lowerEqual)},
		{">=",       std::make_shared<Value>(BuiltinFunctions::greaterEqual)},
		{"=",        std::make_shared<Value>(BuiltinFunctions::equal)},
		{"is",       std::make_shared<Value>(BuiltinFunctions::equal)},
		{"!=",       std::make_shared<Value>(BuiltinFunctions::notEqual)},
		{"and",      std::make_shared<Value>(BuiltinFunctions::and_)},
		{"or",       std::make_shared<Value>(BuiltinFunctions::or_)},
		{"+",        std::make_shared<Value>(BuiltinFunctions::add)},
		{"-",        std::make_shared<Value>(BuiltinFunctions::substract)},
		{"*",        std::make_shared<Value>(BuiltinFunctions::multiply)},
		{"/",        std::make_shared<Value>(BuiltinFunctions::divide)},
		{"%",        std::make_shared<Value>(BuiltinFunctions::modulo)},
		{"!",        std::make_shared<Value>(BuiltinFunctions::not_)},
		{"define",   std::make_shared<Value>(BuiltinCallables::define)},
		{"if",       std::make_shared<Value>(BuiltinCallables::if_)},
		{"function", std::make_shared<Value>(BuiltinCallables::defineFunction)},
		{"true",     std::make_shared<Value>(true)},
		{"false",    std::make_shared<Value>(false)},
		{"null",     std::make_shared<Value>(Null())},
	}}
{
}

void Interpreter::loadFromStream(std::istream& stream)
{
	const std::string fileContent{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
	_evaluationTree = _parser.constructMultipleTrees(fileContent);
}

Value Interpreter::interpret()
{
	return BuiltinCallables::evaluate(_evaluationTree, _globalScope);
}
