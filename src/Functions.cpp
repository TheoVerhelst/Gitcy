#include <iostream>
#include <Interpreter.hpp>
#include <Functions.hpp>

BuiltinFunctions::BuiltinFunctions():
	#define OVERLOAD(className) std::make_shared<BuiltinOverloads::className>()
	print{{OVERLOAD(Print)}},
	do_{{OVERLOAD(Do)}},
	define{{OVERLOAD(Define)}},
	lowerThan{{OVERLOAD(LowerThan<int>), OVERLOAD(LowerThan<double>)}},
	greaterThan{{OVERLOAD(GreaterThan<int>), OVERLOAD(GreaterThan<double>)}},
	lowerEqual{{OVERLOAD(LowerEqual<int>), OVERLOAD(LowerEqual<double>)}},
	greaterEqual{{OVERLOAD(GreaterEqual<int>), OVERLOAD(GreaterEqual<double>)}},
	equal{{OVERLOAD(Equal<int>), OVERLOAD(Equal<double>), OVERLOAD(Equal<std::string>), OVERLOAD(Equal<bool>)}},
	notEqual{{OVERLOAD(NotEqual<int>), OVERLOAD(NotEqual<double>), OVERLOAD(NotEqual<std::string>), OVERLOAD(NotEqual<bool>)}},
	and_{{OVERLOAD(And)}},
	or_{{OVERLOAD(Or)}},
	add{{OVERLOAD(Add<int>), OVERLOAD(Add<double>), OVERLOAD(Add<std::string>)}},
	substract{{OVERLOAD(Substract<int>), OVERLOAD(Substract<double>)}},
	multiply{{OVERLOAD(Multiply<int>), OVERLOAD(Multiply<double>)}},
	divide{{OVERLOAD(Divide<int>), OVERLOAD(Divide<double>)}},
	modulo{{OVERLOAD(Modulo), OVERLOAD(DoubleModulo)}},
	not_{{OVERLOAD(Not)}}
	#undef OVERLOAD
{
}

namespace BuiltinOverloads
{
	Print::Print():
		Overload{{}, true}
	{
	}

	Data Print::operator()(const std::vector<Data>& arguments) const
	{
		std::cout << std::boolalpha << Utils::join(" ", arguments.begin(), arguments.end()) << std::endl;
		return Null();
	}

	Do::Do():
		Overload{{}, true}
	{
	}

	Data Do::operator()(const std::vector<Data>& arguments) const
	{
		if(arguments.empty())
			return Null();
		return arguments.back();
	}

	Define::Define():
		Overload{{SignatureType::create<std::string>(), SignatureType::create()}, false}
	{
	}

	Data Define::operator()(const std::vector<Data>& arguments) const
	{
		const Data value{arguments.at(1)};
		// TODO // _interpreter._variables.emplace(arguments.at(0).get<std::string>(), std::make_shared<Data>(value));
		return value;
	}

	And::And():
		Overload{{SignatureType::create<bool>()}, true}
	{
	}

	Data And::operator()(const std::vector<Data>& arguments) const
	{
		const std::vector<bool> convertedArguments{Utils::convert<bool>(arguments)};
		return std::find(convertedArguments.begin(), convertedArguments.end(), false) == convertedArguments.end();
	}

	Or::Or():
		Overload{{SignatureType::create<bool>()}, true}
	{
	}

	Data Or::operator()(const std::vector<Data>& arguments) const
	{
		const std::vector<bool> convertedArguments{Utils::convert<bool>(arguments)};
		return std::find(convertedArguments.begin(), convertedArguments.end(), true) != convertedArguments.end();
	}

	Modulo::Modulo():
		Overload{{SignatureType::create<int>(), SignatureType::create<int>()}, false}
	{
	}

	Data Modulo::operator()(const std::vector<Data>& arguments) const
	{
		Data lhs(arguments[0]), rhs(arguments[1]);
		if(rhs.get<int>() == 0)
			throw ScriptError("modulo by zero");
		return lhs.get<int>() % rhs.get<int>();
	}

	DoubleModulo::DoubleModulo():
		Overload{{SignatureType::create<double>(), SignatureType::create<double>()}, false}
	{
	}

	Data DoubleModulo::operator()(const std::vector<Data>& arguments) const
	{
		Data lhs(arguments[0]), rhs(arguments[1]);
		if(rhs.get<double>() == 0.)
			throw ScriptError("modulo by zero");
		return std::fmod(lhs.get<double>(), rhs.get<double>());
	}

	Not::Not():
		Overload{{SignatureType::create<bool>()}, false}
	{
	}

	Data Not::operator()(const std::vector<Data>& arguments) const
	{
		Data lhs(arguments[0]);
		return not lhs.get<bool>();
	}
}
