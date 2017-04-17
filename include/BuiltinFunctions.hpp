#ifndef BUILTIN_FUNCTIONS_HPP
#define BUILTIN_FUNCTIONS_HPP

#include <Function.hpp>

/// Holds all functions that are written in C++ but callable in scripts.
/// These functions are public const variables, and are initialized in the
/// constructor.
class BuiltinFunctions
{
	public:
		/// Constructor.
		BuiltinFunctions();

		const Function print;        ///< Prints the arguments to stdout.
		const Function do_;          ///< Just evaluates its arguments, and returns the last.
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
};

#endif // BUILTIN_FUNCTIONS_HPP
