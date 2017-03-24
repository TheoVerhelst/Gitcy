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
		{{SignatureType::create<std::string>(), SignatureType::create()}, false, BOUND(_define)}
	}},
	lowerThan{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, true, BOUND(_lowerThan<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, true, BOUND(_lowerThan<double>)}
	}},
	greaterThan{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, true, BOUND(_greaterThan<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, true, BOUND(_greaterThan<double>)}
	}},

	lowerEqual{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, true, BOUND(_lowerEqual<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, true, BOUND(_lowerEqual<double>)}
	}},

	greaterEqual{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, true, BOUND(_greaterEqual<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, true, BOUND(_greaterEqual<double>)}
	}},

	equal{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, true, BOUND(_equal<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, true, BOUND(_equal<double>)},
		{{SignatureType::create<std::string>(), SignatureType::create<std::string>()}, true, BOUND(_equal<std::string>)},
		{{SignatureType::create<bool>(), SignatureType::create<bool>()}, true, BOUND(_equal<bool>)}
	}},

	notEqual{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, false, BOUND(_notEqual<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, false, BOUND(_notEqual<double>)},
		{{SignatureType::create<std::string>(), SignatureType::create<std::string>()}, false, BOUND(_notEqual<std::string>)},
		{{SignatureType::create<bool>(), SignatureType::create<bool>()}, false, BOUND(_notEqual<bool>)}
	}},

	and_{{
		{{SignatureType::create<bool>()}, true, BOUND(_and)}
	}},

	or_{{
		{{SignatureType::create<bool>()}, true, BOUND(_or)}
	}},

	add{{
		{{SignatureType::create<int>()}, true, BOUND(_add<int>)},
		{{SignatureType::create<double>()}, true, BOUND(_add<double>)},
		{{SignatureType::create<std::string>()}, true, BOUND(_add<std::string>)}
	}},

	substract{{
		{{SignatureType::create<int>()}, true, BOUND(_substract<int>)},
		{{SignatureType::create<double>()}, true, BOUND(_substract<double>)}
	}},

	multiply{{
		{{SignatureType::create<int>()}, true, BOUND(_multiply<int>)},
		{{SignatureType::create<double>()}, true, BOUND(_multiply<double>)}
	}},

	divide{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, true, BOUND(_divide<int>)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, true, BOUND(_divide<double>)}
	}},

	modulo{{
		{{SignatureType::create<int>(), SignatureType::create<int>()}, false, BOUND(_modulo)},
		{{SignatureType::create<double>(), SignatureType::create<double>()}, false, BOUND(_fmod)}
	}},
	not_{{
		{{SignatureType::create<bool>()}, false, BOUND(_not)}
	}},
	#undef BOUND
	_interpreter{interpreter}
{
}

Data Functions::_print(const std::vector<Data>& args) const
{
	std::cout << std::boolalpha;
	for(size_t i(0); i < args.size(); ++i)
		std::cout << args[i] << " ";
	std::cout << std::endl;
	return Null();
}

Data Functions::_do(const std::vector<Data>& args) const
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

Data Functions::_and(const std::vector<Data>& args) const
{
	const std::vector<bool> convertedArguments{convert<bool>(args)};
	return std::find(convertedArguments.begin(), convertedArguments.end(), false) == convertedArguments.end();
}

Data Functions::_or(const std::vector<Data>& args) const
{
	const std::vector<bool> convertedArguments{convert<bool>(args)};
	return std::find(convertedArguments.begin(), convertedArguments.end(), true) != convertedArguments.end();
}

Data Functions::_modulo(const std::vector<Data>& args) const
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<int>(rhs) == static_cast<int>(0))
		throw ScriptError("modulo by zero");
	return boost::get<int>(lhs) % boost::get<int>(rhs);
}

Data Functions::_fmod(const std::vector<Data>& args) const
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<double>(rhs) == 0.)
		throw ScriptError("modulo by zero");
	return std::fmod(boost::get<double>(lhs), boost::get<double>(rhs));
}

Data Functions::_not(const std::vector<Data>& args) const
{
	Data lhs(args[0]);
	return not boost::get<bool>(lhs);
}

