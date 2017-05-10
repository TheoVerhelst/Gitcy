#ifndef BUILTIN_FUNCTIONS_HPP
#define BUILTIN_FUNCTIONS_HPP

#include <Function.hpp>
#include <Callable.hpp>

/// Holds all functions that are written in C++ but callable in scripts.
/// These functions are public const variables, and are initialized in the
/// constructor.
class BuiltinFunctions
{
	public:
		static const Callable print;        ///< Prints the arguments to stdout.
		static const Callable do_;          ///< Just evaluates its arguments, and returns the last.
		static const Callable lowerThan;    ///< Checks if first argument is lower than second.
		static const Callable greaterThan;  ///< Checks if first argument is greater than second.
		static const Callable lowerEqual;   ///< Checks if first argument is lower of equal to the second.
		static const Callable greaterEqual; ///< Checks if first argument is greater or equal to the second.
		static const Callable equal;        ///< Checks if first argument is equal to the second.
		static const Callable notEqual;     ///< Checks if first argument is not equal to the second.
		static const Callable and_;         ///< Returns the logical and between first and second argument.
		static const Callable or_;          ///< Returns the logical and between first and second argument.
		static const Callable add;          ///< Returns the arithmetic addition between its arguments.
		static const Callable substract;    ///< Returns the arithmetic substraction between its arguments.
		static const Callable multiply;     ///< Returns the arithmetic multiplication between its arguments.
		static const Callable divide;       ///< Returns the arithmetic division between its arguments.
		static const Callable modulo;       ///< Returns the arithmetic modulo between its arguments.
		static const Callable not_;         ///< Returns the logical not of its argument.
};

#endif // BUILTIN_FUNCTIONS_HPP
