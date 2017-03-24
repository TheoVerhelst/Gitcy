#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <cmath>
#include <Data.hpp>
#include <ScriptError.hpp>
#include <Function.hpp>

// Forward declarations
class Interpreter;

/// Holds all functions that are written in C++ but callable in scripts.
/// These functions are public const variables, and are initialized in the
/// constructor. This class also contains the code of the implementation of
/// these functions, properly bound with the Overload class.
class Functions
{
	public:
		/// Constructor.
		/// \param interpreter A reference to the interpreter. We use this
		/// because any functions may modify the interpreter state (such as
		/// variables). \TODO make some of the method const, in order to
		/// guarantee functional purity.
		Functions(Interpreter& interpreter);

		const Function print;        ///< Prints the arguments to stdout.
		const Function do_;          ///< Just evaluates its arguments, and returns the last.
		const Function define;       ///< Binds a value to a name.
		const Function lowerThan;    ///< Checks if first argument is lower than second. \TODO make it variadic.
		const Function greaterThan;  ///< Checks if first argument is greater than second.
		const Function lowerEqual;   ///< Checks if first argument is lower of equal to the second.
		const Function greaterEqual; ///< Checks if first argument is greater or equal to the second.
		const Function equal;        ///< Checks if first argument is equal to the second.
		const Function notEqual;     ///< Checks if first argument is not equal to the second.
		const Function and_;         ///< Returns the logical and between first and second argument.
		const Function or_;          ///< Returns the logical and between first and second argument.
		const Function add;          ///< Returns the arithmetic addition between its arguments.
		const Function substract;    ///< Returns the arithmetic substraction between its arguments.
		const Function multiply;     ///< Returns the arithmetic multiplication between its arguments.
		const Function divide;       ///< Returns the arithmetic division between its arguments.
		const Function modulo;       ///< Returns the arithmetic modulo between its arguments.
		const Function not_;         ///< Returns the logical not of its argument.

	private:
		/// Implements print.
		/// \param args The argument list.
		Data _print(const std::vector<Data>& args);

		/// Implements do.
		/// \param args The argument list.
		Data _do(const std::vector<Data>& args);

		/// Implements define.
		/// \param args The argument list.
		Data _define(const std::vector<Data>& args);

		/// Implements lowerThan.
		/// \param args The argument list.
		/// \tparam T Either int or double
		template <typename T>
		Data _lowerThan(const std::vector<Data>& args);

		/// Implements greaterThan.
		/// \param args The argument list.
		/// \tparam T Either int or double
		template <typename T>
		Data _greaterThan(const std::vector<Data>& args);

		/// Implements lowerEqual.
		/// \param args The argument list.
		/// \tparam T Either int or double
		template <typename T>
		Data _lowerEqual(const std::vector<Data>& args);

		/// Implements greaterEqual.
		/// \param args The argument list.
		/// \tparam T Either int or double
		template <typename T>
		Data _greaterEqual(const std::vector<Data>& args);

		/// Implements equal.
		/// \param args The argument list.
		/// \tparam T Either int, double, std::string or \TODO bool
		template <typename T>
		Data _equal(const std::vector<Data>& args);

		/// Implements notEqual.
		/// \param args The argument list.
		/// \tparam T Either int, double, std::string or \TODO bool
		template <typename T>
		Data _notEqual(const std::vector<Data>& args);

		/// Implements and.
		/// \param args The argument list.
		Data _and(const std::vector<Data>& args);

		/// Implements or.
		/// \param args The argument list.
		Data _or(const std::vector<Data>& args);

		/// Implements add.
		/// \param args The argument list.
		/// \tparam T Either int, double or string.
		template <typename T>
		Data _add(const std::vector<Data>& args);

		/// Implements substract.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _substract(const std::vector<Data>& args);

		/// Implements multiply.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _multiply(const std::vector<Data>& args);

		/// Implements divide.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _divide(const std::vector<Data>& args);

		/// Implements modulo for integers.
		/// \param args The argument list.
		Data _modulo(const std::vector<Data>& args);

		/// Implements modulo for double.
		/// \param args The argument list.
		Data _fmod(const std::vector<Data>& args);

		/// Implements not.
		/// \param args The argument list.
		Data _not(const std::vector<Data>& args);

		/// A reference to the interpreter, allows functions to have
		/// side-effects.
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
