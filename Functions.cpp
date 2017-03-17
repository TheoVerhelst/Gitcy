#include <iostream>
#include <cmath>
#include "Interpreter.hpp"
#include "Function.hpp"
#include "Functions.hpp"

Functions::Functions(Interpreter& interpreter):
	m_interpreter{interpreter}
{
}

Data Functions::print(const std::vector<Data>& args)
{
	std::cout << std::boolalpha;
	for(size_t i(0); i < args.size(); ++i)
		std::cout << args[i] << " ";
	std::cout << std::endl;
	return 0;
}

Data Functions::do_(const std::vector<Data>& args)
{
	return 0;
}

Data Functions::define(const std::vector<Data>& args)
{
	Data name(args.at(0)), value(args.at(1));
	if(name.type() != typeid(std::string))
		throw std::runtime_error("first argument must be a string in define");
	else
		m_interpreter.m_variables.emplace(boost::get<std::string>(name), std::make_shared<Data>(value));
	return value;
}

Data Functions::lowerThan(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(lhs.type() != typeid(std::string) and rhs.type() != typeid(std::string))
	{
		if(lhs.type() != typeid(float) and rhs.type() != typeid(float))
		{
			cast<int>(lhs);
			cast<int>(rhs);
			return boost::get<int>(lhs) < boost::get<int>(rhs);
		}
		else
		{
			cast<float>(lhs);
			cast<float>(rhs);
			return boost::get<float>(lhs) < boost::get<float>(rhs);
		}
	}
	else if(lhs.type() == typeid(std::string)
			and rhs.type() == typeid(std::string))
		return boost::get<std::string>(lhs).size()
			< boost::get<std::string>(rhs).size();
	else
		throw std::runtime_error("invalid operands types for comparaison.");
}

Data Functions::greaterThan(const std::vector<Data>& args)
{
	return lowerThan({args[1], args[0]});
}

Data Functions::lowerEqual(const std::vector<Data>& args)
{
	return not_({greaterThan(args)});
}

Data Functions::greaterEqual(const std::vector<Data>& args)
{
	return not_({lowerThan(args)});
}

Data Functions::equal(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	//Both are string
	if(lhs.type() == typeid(std::string) and rhs.type() == typeid(std::string))
		return boost::get<std::string>(args[0]) == boost::get<std::string>(args[1]);
	//One is string
	else if(lhs.type() == typeid(std::string) or rhs.type() == typeid(std::string))
		return false;
	//Both are numeric
	else
		return and_({greaterEqual(args), lowerEqual(args)});
}

Data Functions::notEqual(const std::vector<Data>& args)
{
	return not_({equal(args)});
}

Data Functions::and_(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	cast<bool>(lhs);
	cast<bool>(rhs);
	return boost::get<bool>(lhs) and boost::get<bool>(rhs);
}

Data Functions::or_(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	cast<bool>(lhs);
	cast<bool>(rhs);
	return boost::get<bool>(lhs) or boost::get<bool>(rhs);
}

Data Functions::add(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(lhs.type() == typeid(std::string) or rhs.type() == typeid(std::string))
	{
		cast<std::string>(lhs);
		cast<std::string>(rhs);
		return boost::get<std::string>(lhs) + boost::get<std::string>(rhs);
	}
	else if(lhs.type() == typeid(float) or rhs.type() == typeid(float))
	{
		cast<float>(lhs);
		cast<float>(rhs);
		return boost::get<float>(lhs) + boost::get<float>(rhs);
	}
	else if(lhs.type() == typeid(int) or rhs.type() == typeid(int))
	{
		cast<int>(lhs);
		cast<int>(rhs);
		return boost::get<int>(lhs) + boost::get<int>(rhs);
	}
	else
		return static_cast<bool>(boost::get<bool>(lhs) + boost::get<bool>(rhs));
}

Data Functions::substract(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(lhs.type() == typeid(std::string) or rhs.type() == typeid(std::string))
		throw std::runtime_error("String does not support substraction");
	else if(lhs.type() == typeid(float) or rhs.type() == typeid(float))
	{
		cast<float>(lhs);
		cast<float>(rhs);
		return boost::get<float>(lhs) - boost::get<float>(rhs);
	}
	else if(lhs.type() == typeid(int) or rhs.type() == typeid(int))
	{
		cast<int>(lhs);
		cast<int>(rhs);
		return boost::get<int>(lhs) - boost::get<int>(rhs);
	}
	else
		return static_cast<bool>(boost::get<bool>(lhs) + boost::get<bool>(rhs));
}

Data Functions::multiply(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(lhs.type() == typeid(std::string) or rhs.type() == typeid(std::string))
		throw std::runtime_error("String does not support multiplication.");
	else if(lhs.type() == typeid(float) or rhs.type() == typeid(float))
	{
		cast<float>(lhs);
		cast<float>(rhs);
		return boost::get<float>(lhs) * boost::get<float>(rhs);
	}
	else if(lhs.type() == typeid(int) or rhs.type() == typeid(int))
	{
		cast<int>(lhs);
		cast<int>(rhs);
		return boost::get<int>(lhs) * boost::get<int>(rhs);
	}
	else
		return static_cast<bool>(boost::get<bool>(lhs) * boost::get<bool>(rhs));
}

Data Functions::divide(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(lhs.type() == typeid(std::string) or rhs.type() == typeid(std::string))
		throw std::runtime_error("string does not support division.");
	else if(lhs.type() == typeid(float) or rhs.type() == typeid(float))
	{
		cast<float>(lhs);
		cast<float>(rhs);
		if(boost::get<float>(rhs) == 0.f)
			throw std::runtime_error("division by zero");
		return boost::get<float>(lhs) / boost::get<float>(rhs);
	}
	else if(lhs.type() == typeid(int) or rhs.type() == typeid(int))
	{
		cast<int>(lhs);
		cast<int>(rhs);
		if(boost::get<int>(rhs) == 0)
			throw std::runtime_error("division by zero");
		return boost::get<int>(lhs) / boost::get<int>(rhs);
	}
	else
		throw std::runtime_error("boolean does not support division.");
}

Data Functions::modulo(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(lhs.type() == typeid(std::string) or rhs.type() == typeid(std::string))
		throw std::runtime_error("string does not support modulo.");
	else if(lhs.type() == typeid(float) or rhs.type() == typeid(float))
	{
		cast<float>(lhs);
		cast<float>(rhs);
		if(boost::get<float>(rhs) == 0.f)
			throw std::runtime_error("modulo by zero");
		return static_cast<float>(std::fmod(boost::get<float>(lhs), boost::get<float>(rhs)));
	}
	else if(lhs.type() == typeid(int) or rhs.type() == typeid(int))
	{
		cast<int>(lhs);
		cast<int>(rhs);
		if(boost::get<int>(rhs) == 0)
			throw std::runtime_error("modulo by zero");
		return boost::get<int>(lhs) % boost::get<int>(rhs);
	}
	else
		throw std::runtime_error("boolean does not support modulo.");
}

Data Functions::not_(const std::vector<Data>& args)
{
	Data lhs(args[0]);
	cast<bool>(lhs);
	return not boost::get<bool>(lhs);
}

