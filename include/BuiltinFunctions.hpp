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

		const std::shared_ptr<Callable> print;        ///< Prints the arguments to stdout.
		const std::shared_ptr<Callable> do_;          ///< Just evaluates its arguments, and returns the last.
		const std::shared_ptr<Callable> lowerThan;    ///< Checks if first argument is lower than second.
		const std::shared_ptr<Callable> greaterThan;  ///< Checks if first argument is greater than second.
		const std::shared_ptr<Callable> lowerEqual;   ///< Checks if first argument is lower of equal to the second.
		const std::shared_ptr<Callable> greaterEqual; ///< Checks if first argument is greater or equal to the second.
		const std::shared_ptr<Callable> equal;        ///< Checks if first argument is equal to the second.
		const std::shared_ptr<Callable> notEqual;     ///< Checks if first argument is not equal to the second.
		const std::shared_ptr<Callable> and_;         ///< Returns the logical and between first and second argument.
		const std::shared_ptr<Callable> or_;          ///< Returns the logical and between first and second argument.
		const std::shared_ptr<Callable> add;          ///< Returns the arithmetic addition between its arguments.
		const std::shared_ptr<Callable> substract;    ///< Returns the arithmetic substraction between its arguments.
		const std::shared_ptr<Callable> multiply;     ///< Returns the arithmetic multiplication between its arguments.
		const std::shared_ptr<Callable> divide;       ///< Returns the arithmetic division between its arguments.
		const std::shared_ptr<Callable> modulo;       ///< Returns the arithmetic modulo between its arguments.
		const std::shared_ptr<Callable> not_;         ///< Returns the logical not of its argument.
};

#endif // BUILTIN_FUNCTIONS_HPP
