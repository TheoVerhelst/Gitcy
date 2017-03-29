#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <Function.hpp>

// Forward declarations
class Interpreter;
class Data;

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
		/// variables).
		Functions(Interpreter& interpreter);

		const Function print;        ///< Prints the arguments to stdout.
		const Function do_;          ///< Just evaluates its arguments, and returns the last.
		const Function define;       ///< Binds a value to a name.
		const Function lowerThan;    ///< Checks if first argument is lower than second.
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
		Data _print(const std::vector<Data>& args) const;

		/// Implements do.
		/// \param args The argument list.
		Data _do(const std::vector<Data>& args) const;

		/// Implements define.
		/// \param args The argument list.
		Data _define(const std::vector<Data>& args);

		/// Implements lowerThan.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _lowerThan(const std::vector<Data>& args) const;

		/// Implements greaterThan.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _greaterThan(const std::vector<Data>& args) const;

		/// Implements lowerEqual.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _lowerEqual(const std::vector<Data>& args) const;

		/// Implements greaterEqual.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _greaterEqual(const std::vector<Data>& args) const;

		/// Implements equal.
		/// \param args The argument list.
		/// \tparam T Either int, double, std::string or bool.
		template <typename T>
		Data _equal(const std::vector<Data>& args) const;

		/// Implements notEqual.
		/// \param args The argument list.
		/// \tparam T Either int, double, std::string or bool.
		template <typename T>
		Data _notEqual(const std::vector<Data>& args) const;

		/// Implements and.
		/// \param args The argument list.
		Data _and(const std::vector<Data>& args) const;

		/// Implements or.
		/// \param args The argument list.
		Data _or(const std::vector<Data>& args) const;

		/// Implements add.
		/// \param args The argument list.
		/// \tparam T Either int, double or string.
		template <typename T>
		Data _add(const std::vector<Data>& args) const;

		/// Implements substract.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _substract(const std::vector<Data>& args) const;

		/// Implements multiply.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _multiply(const std::vector<Data>& args) const;

		/// Implements divide.
		/// \param args The argument list.
		/// \tparam T Either int or double.
		template <typename T>
		Data _divide(const std::vector<Data>& args) const;

		/// Implements modulo for integers.
		/// \param args The argument list.
		Data _modulo(const std::vector<Data>& args) const;

		/// Implements modulo for double.
		/// \param args The argument list.
		Data _fmod(const std::vector<Data>& args) const;

		/// Implements not.
		/// \param args The argument list.
		Data _not(const std::vector<Data>& args) const;

		template <typename T>
		static std::vector<T> convert(const std::vector<Data>& args);

		/// A reference to the interpreter, allows functions to have
		/// side-effects.
		Interpreter& _interpreter;
};

#include <Data.hpp>
#include <ScriptError.hpp>

template <typename T>
Data Functions::_lowerThan(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::greater_equal<T>()) == convertedArguments.end();
}

template <typename T>
Data Functions::_greaterThan(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::less_equal<T>()) == convertedArguments.end();
}

template <typename T>
Data Functions::_lowerEqual(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::greater<T>()) == convertedArguments.end();
}

template <typename T>
Data Functions::_greaterEqual(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::less<T>()) == convertedArguments.end();
}

template <typename T>
Data Functions::_equal(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::adjacent_find(convertedArguments.begin(), convertedArguments.end(), std::not_equal_to<T>()) == convertedArguments.end();
}

template <typename T>
Data Functions::_notEqual(const std::vector<Data>& args) const
{
	return _not({_equal<T>(args)});
}

template <typename T>
Data Functions::_add(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::accumulate(convertedArguments.begin(), convertedArguments.end(), T());
}

template <typename T>
Data Functions::_substract(const std::vector<Data>& args) const
{
	if(args.size() == 1)
		return -args.front().get<T>();
	else
	{
		const std::vector<T> convertedArguments{convert<T>(args)};
		return std::accumulate(std::next(convertedArguments.begin()), convertedArguments.end(), convertedArguments.front(), std::minus<T>());
	}
}

template <typename T>
Data Functions::_multiply(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	return std::accumulate(convertedArguments.begin(), convertedArguments.end(), static_cast<T>(1), std::multiplies<T>());
}

template <typename T>
Data Functions::_divide(const std::vector<Data>& args) const
{
	const std::vector<T> convertedArguments{convert<T>(args)};
	// If there is a zero in the values [begin + 1, end)
	if(std::find(std::next(convertedArguments.begin()), convertedArguments.end(), static_cast<T>(0)) != convertedArguments.end())
		throw ScriptError("division by zero");
	return std::accumulate(std::next(convertedArguments.begin()), convertedArguments.end(), convertedArguments.front(), std::divides<T>());
}

template <typename T>
std::vector<T> Functions::convert(const std::vector<Data>& args)
{
	std::vector<T> convertedArguments;
	std::transform(args.begin(), args.end(), std::back_inserter(convertedArguments),
			[](const Data& data)
			{
				return data.get<T>();
			});
	return convertedArguments;
}

#endif
