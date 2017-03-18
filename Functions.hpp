#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <cmath>
#include "Data.hpp"
#include "ScriptError.hpp"
#include "Function.hpp"

class Interpreter;

class Functions
{
	public:
		/// Constructor.
		Functions(Interpreter& erpreter);

		const Function print;
		const Function do_;
		const Function define;
		const Function lowerThan;
		const Function greaterThan;
		const Function lowerEqual;
		const Function greaterEqual;
		const Function equal;
		const Function notEqual;
		const Function and_;
		const Function or_;
		const Function add;
		const Function substract;
		const Function multiply;
		const Function divide;
		const Function modulo;
		const Function not_;

	private:
		Data _print(const std::vector<Data>& args);
		Data _do(const std::vector<Data>& args);
		Data _define(const std::vector<Data>& args);
		template <typename T>
		Data _lowerThan(const std::vector<Data>& args);
		template <typename T>
		Data _greaterThan(const std::vector<Data>& args);
		template <typename T>
		Data _lowerEqual(const std::vector<Data>& args);
		template <typename T>
		Data _greaterEqual(const std::vector<Data>& args);
		template <typename T>
		Data _equal(const std::vector<Data>& args);
		template <typename T>
		Data _notEqual(const std::vector<Data>& args);
		Data _and(const std::vector<Data>& args);
		Data _or(const std::vector<Data>& args);
		template <typename T>
		Data _add(const std::vector<Data>& args);
		template <typename T>
		Data _substract(const std::vector<Data>& args);
		template <typename T>
		Data _multiply(const std::vector<Data>& args);
		template <typename T>
		Data _divide(const std::vector<Data>& args);
		Data _modulo(const std::vector<Data>& args);
		Data _fmod(const std::vector<Data>& args);
		Data _not(const std::vector<Data>& args);

		Interpreter& _interpreter;
};

template <typename T>
Data Functions::_lowerThan(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<T>(lhs) < boost::get<T>(rhs);
}

template <typename T>
Data Functions::_greaterThan(const std::vector<Data>& args)
{
	return _lowerThan<T>({args[1], args[0]});
}

template <typename T>
Data Functions::_lowerEqual(const std::vector<Data>& args)
{
	return _not({_greaterThan<T>(args)});
}

template <typename T>
Data Functions::_greaterEqual(const std::vector<Data>& args)
{
	return _not({_lowerThan<T>(args)});
}

template <typename T>
Data Functions::_equal(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<T>(lhs) < boost::get<T>(rhs);
}

template <typename T>
Data Functions::_notEqual(const std::vector<Data>& args)
{
	return _not({_equal<T>(args)});
}

template <typename T>
Data Functions::_add(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<T>(lhs) + boost::get<T>(rhs);
}

template <typename T>
Data Functions::_substract(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<T>(lhs) - boost::get<T>(rhs);
}

template <typename T>
Data Functions::_multiply(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	return boost::get<T>(lhs) * boost::get<T>(rhs);
}

template <typename T>
Data Functions::_divide(const std::vector<Data>& args)
{
	Data lhs(args[0]), rhs(args[1]);
	if(boost::get<T>(rhs) == static_cast<T>(0))
		throw ScriptError("division by zero");
	return boost::get<T>(lhs) / boost::get<T>(rhs);
}

#endif
