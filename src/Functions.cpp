#include <iostream>
#include <Interpreter.hpp>
#include <Function.hpp>
#include <Functions.hpp>

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
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_lowerThan<double>)}
	}},
	greaterThan{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_greaterThan<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_greaterThan<double>)}
	}},

	lowerEqual{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_lowerEqual<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_lowerEqual<double>)}
	}},

	greaterEqual{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_greaterEqual<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_greaterEqual<double>)}
	}},

	equal{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_equal<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_equal<double>)},
		{{{typeid(std::string)}, {typeid(std::string)}}, false, BOUND(_equal<std::string>)},
		{{{typeid(bool)}, {typeid(bool)}}, false, BOUND(_equal<bool>)}
	}},

	notEqual{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_notEqual<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_notEqual<double>)},
		{{{typeid(std::string)}, {typeid(std::string)}}, false, BOUND(_notEqual<std::string>)},
		{{{typeid(bool)}, {typeid(bool)}}, false, BOUND(_notEqual<bool>)}
	}},

	and_{{
		{{{typeid(bool)}, {typeid(bool)}}, false, BOUND(_and)}
	}},

	or_{{
		{{{typeid(bool)}, {typeid(bool)}}, false, BOUND(_or)}
	}},

	add{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_add<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_add<double>)},
		{{{typeid(std::string)}, {typeid(std::string)}}, false, BOUND(_add<std::string>)}
	}},

	substract{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_substract<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_substract<double>)}
	}},

	multiply{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_multiply<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_multiply<double>)}
	}},

	divide{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_divide<int>)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_divide<double>)}
	}},

	modulo{{
		{{{typeid(int)}, {typeid(int)}}, false, BOUND(_modulo)},
		{{{typeid(double)}, {typeid(double)}}, false, BOUND(_fmod)}
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
	if(boost::get<double>(rhs) == 0.)
		throw ScriptError("modulo by zero");
	return std::fmod(boost::get<double>(lhs), boost::get<double>(rhs));
}

Data Functions::_not(const std::vector<Data>& args)
{
	Data lhs(args[0]);
	return not boost::get<bool>(lhs);
}
