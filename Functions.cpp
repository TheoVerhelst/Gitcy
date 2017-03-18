#include <iostream>
#include "Interpreter.hpp"
#include "Function.hpp"
#include "Functions.hpp"

Functions::Functions(Interpreter& interpreter):
	#define BOUND(methodeName) std::bind(&Functions::methodeName, this, std::placeholders::_1)
	print{{
		{{}, true, BOUND(_print)}
	}},
	do_{{
		{{}, true, BOUND(_do)}
	}},
	define{{
		{{{typeid(std::string)}, {}}, false, BOUND(_define)}
	}},
	lowerThan{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_lowerThan<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_lowerThan<float>)}
	}},
	greaterThan{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_greaterThan<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_greaterThan<float>)}
	}},

	lowerEqual{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_lowerEqual<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_lowerEqual<float>)}
	}},

	greaterEqual{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_greaterEqual<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_greaterEqual<float>)}
	}},

	equal{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_equal<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_equal<float>)},
		{{{typeid(std::string)}, {typeid(std::string)}}, false, BOUND(_equal<std::string>)}
	}},

	notEqual{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_notEqual<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_notEqual<float>)},
		{{{typeid(std::string)}, {typeid(std::string)}}, false, BOUND(_notEqual<std::string>)}
	}},

	and_{{
		{{{typeid(bool)}, {typeid(bool)}}, false, BOUND(_and)}
	}},

	or_{{
		{{{typeid(bool)}, {typeid(bool)}}, false, BOUND(_or)}
	}},

	add{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_add<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_add<float>)},
		{{{typeid(std::string)}, {typeid(std::string)}}, false, BOUND(_add<std::string>)}
	}},

	substract{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_substract<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_substract<float>)}
	}},

	multiply{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_multiply<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_multiply<float>)}
	}},

	divide{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_divide<int>)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_divide<float>)}
	}},

	modulo{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_modulo)},
		{{{typeid(float)}, {typeid(float)}}, false, BOUND(_fmod)}
	}},
	not_{{
		{{{typeid(bool)}}, false, BOUND(_not)}
	}},
	#undef BOUND
	_interpreter{interpreter}
{
}

Data Functions::_print(const std::vector<Data>& args)
{
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

Data Functions::_modulo(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<int>(rhs) == static_cast<int>(0))
		throw ScriptError("modulo by zero");
	return boost::get<int>(lhs) % boost::get<int>(rhs);
}

Data Functions::_fmod(const std::vector<Data>& args)
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

