#include <iostream>
#include <cmath>
#include <Null.hpp>
#include <BuiltinFunctionsOverloads.hpp>

namespace BuiltinFunctionsOverloads
{
	Print::Print():
		Overload{{}, true}
	{
	}

	Value Print::call(const std::vector<Value>& arguments) const
	{
		std::cout << std::boolalpha << Utils::join(" ", arguments.begin(), arguments.end()) << std::endl;
		return Null();
	}

	Do::Do():
		Overload{{}, true}
	{
	}

	Value Do::call(const std::vector<Value>& arguments) const
	{
		if(arguments.empty())
			return Null();
		return arguments.back();
	}
	
	And::And():
		Overload{{SignatureType::create<bool>()}, true}
	{
	}

	Value And::call(const std::vector<Value>& arguments) const
	{
		const std::vector<bool> convertedArguments{Utils::convert<bool>(arguments)};
		return std::find(convertedArguments.begin(), convertedArguments.end(), false) == convertedArguments.end();
	}

	Or::Or():
		Overload{{SignatureType::create<bool>()}, true}
	{
	}

	Value Or::call(const std::vector<Value>& arguments) const
	{
		const std::vector<bool> convertedArguments{Utils::convert<bool>(arguments)};
		return std::find(convertedArguments.begin(), convertedArguments.end(), true) != convertedArguments.end();
	}

	Modulo::Modulo():
		Overload{{SignatureType::create<int>(), SignatureType::create<int>()}, false}
	{
	}

	Value Modulo::call(const std::vector<Value>& arguments) const
	{
		Value lhs(arguments[0]), rhs(arguments[1]);
		if(rhs.get<int>() == 0)
			throw ScriptError("modulo by zero");
		return lhs.get<int>() % rhs.get<int>();
	}

	DoubleModulo::DoubleModulo():
		Overload{{SignatureType::create<double>(), SignatureType::create<double>()}, false}
	{
	}

	Value DoubleModulo::call(const std::vector<Value>& arguments) const
	{
		Value lhs(arguments[0]), rhs(arguments[1]);
		if(rhs.get<double>() == 0.)
			throw ScriptError("modulo by zero");
		return std::fmod(lhs.get<double>(), rhs.get<double>());
	}

	Not::Not():
		Overload{{SignatureType::create<bool>()}, false}
	{
	}

	Value Not::call(const std::vector<Value>& arguments) const
	{
		Value lhs(arguments[0]);
		return not lhs.get<bool>();
	}
}
