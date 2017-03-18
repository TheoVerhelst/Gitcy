#include <iostream>
#include <cmath>
#include "Interpreter.hpp"
#include "Function.hpp"
#include "ScriptError.hpp"
#include "Functions.hpp"

Functions::Functions(Interpreter& interpreter):
	#define BOUND(methodeName) std::bind(&Functions::methodeName, this, std::placeholders::_1)
	print{{{
		{{{}, true}, BOUND(_print)}
	}}},
	do_{{{
		{{{}, true}, BOUND(_do)}
	}}},
	define{{{
		{{{{typeid(std::string)}, {}}, false}, BOUND(_define)}
	}}},
	lowerThan{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_lowerThanInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_lowerThanFloat)}
	}}},
	greaterThan{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_greaterThanInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_greaterThanFloat)}
	}}},

	lowerEqual{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_lowerEqualInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_lowerEqualFloat)}
	}}},

	greaterEqual{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_greaterEqualInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_greaterEqualFloat)}
	}}},

	equal{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_equalInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_equalFloat)},
		{{{{typeid(std::string)}, {typeid(std::string)}}, false}, BOUND(_equalString)}
	}}},

	notEqual{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_notEqualInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_notEqualFloat)},
		{{{{typeid(std::string)}, {typeid(std::string)}}, false}, BOUND(_notEqualString)}
	}}},

	and_{{{
		{{{{typeid(bool)}, {typeid(bool)}}, false}, BOUND(_and)}
	}}},

	or_{{{
		{{{{typeid(bool)}, {typeid(bool)}}, false}, BOUND(_or)}
	}}},

	add{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_addInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_addFloat)},
		{{{{typeid(std::string)}, {typeid(std::string)}}, false}, BOUND(_addString)}
	}}},

	substract{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_substractInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_substractFloat)}
	}}},

	multiply{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_multiplyInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_multiplyFloat)}
	}}},

	divide{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_divideInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_divideFloat)}
	}}},

	modulo{{{
		{{{{typeid(int)}, {typeid(int)}}, false}, BOUND(_moduloInt)},
		{{{{typeid(float)}, {typeid(float)}}, false}, BOUND(_moduloFloat)}
	}}},
	not_{{{{{{{typeid(bool)}}, false}, BOUND(_not)}}}},
	#undef BOUND
	_interpreter{interpreter}
{
}

Data Functions::_print(const std::vector<Data>& args)
{
	std::cout << std::boolalpha;
	for(size_t i(0); i < args.size(); ++i)
		std::cout << args[i] << " ";
	std::cout << std::endl;
	return Null();
}

Data Functions::_do(const std::vector<Data>& args)
{
	if(args.empty())
		return Null();
	return args.back();
}

Data Functions::_define(const std::vector<Data>& args)
{
	const Data value{args.at(1)};
	_interpreter._variables.emplace(boost::get<std::string>(args.at(0)), std::make_shared<Data>(value));
	return value;
}

Data Functions::_lowerThanInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<int>(lhs) < boost::get<int>(rhs);
}

Data Functions::_lowerThanFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<float>(lhs) < boost::get<float>(rhs);
}

Data Functions::_greaterThanInt(const std::vector<Data>& args)
{
	return _lowerThanInt({args[1], args[0]});
}

Data Functions::_greaterThanFloat(const std::vector<Data>& args)
{
	return _lowerThanFloat({args[1], args[0]});
}

Data Functions::_lowerEqualInt(const std::vector<Data>& args)
{
	return _not({_greaterThanInt(args)});
}

Data Functions::_lowerEqualFloat(const std::vector<Data>& args)
{
	return _not({_greaterThanFloat(args)});
}

Data Functions::_greaterEqualInt(const std::vector<Data>& args)
{
	return _not({_lowerThanInt(args)});
}

Data Functions::_greaterEqualFloat(const std::vector<Data>& args)
{
	return _not({_lowerThanFloat(args)});
}

Data Functions::_equalInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<int>(lhs) < boost::get<int>(rhs);
}

Data Functions::_equalFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<float>(lhs) < boost::get<float>(rhs);
}

Data Functions::_equalString(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<std::string>(lhs) < boost::get<std::string>(rhs);
}

Data Functions::_notEqualInt(const std::vector<Data>& args)
{
	return _not({_equalInt(args)});
}

Data Functions::_notEqualFloat(const std::vector<Data>& args)
{
	return _not({_equalFloat(args)});
}

Data Functions::_notEqualString(const std::vector<Data>& args)
{
	return _not({_equalString(args)});
}

Data Functions::_and(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<bool>(lhs) and boost::get<bool>(rhs);
}

Data Functions::_or(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<bool>(lhs) or boost::get<bool>(rhs);
}

Data Functions::_addInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<int>(lhs) + boost::get<int>(rhs);
}

Data Functions::_addFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<float>(lhs) + boost::get<float>(rhs);
}

Data Functions::_addString(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<std::string>(lhs) + boost::get<std::string>(rhs);
}

Data Functions::_substractInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<int>(lhs) - boost::get<int>(rhs);
}

Data Functions::_substractFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<float>(lhs) - boost::get<float>(rhs);
}

Data Functions::_multiplyInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<int>(lhs) * boost::get<int>(rhs);
}

Data Functions::_multiplyFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<float>(lhs) * boost::get<float>(rhs);
}

Data Functions::_divideInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<int>(rhs) == 0)
		throw ScriptError("division by zero");
	return boost::get<int>(lhs) / boost::get<int>(rhs);
}

Data Functions::_divideFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<float>(rhs) == 0.f)
		throw ScriptError("division by zero");
	return boost::get<float>(lhs) / boost::get<float>(rhs);
}

Data Functions::_moduloInt(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<int>(rhs) == 0)
		throw ScriptError("modulo by zero");
	return boost::get<int>(lhs) % boost::get<int>(rhs);
}

Data Functions::_moduloFloat(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<float>(rhs) == 0.f)
		throw ScriptError("modulo by zero");
	return std::fmod(boost::get<float>(lhs), boost::get<float>(rhs));
}

Data Functions::_not(const std::vector<Data>& args)
{
	Data lhs(args[0]);
	return not boost::get<bool>(lhs);
}

