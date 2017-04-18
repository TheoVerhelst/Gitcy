#ifndef BUILTIN_CALLABLE_HPP
#define BUILTIN_CALLABLE_HPP

#include <Callable.hpp>

/// Set of callables defining the basic features of the langage.
namespace BuiltinCallables
{
	/// Evaluates an evaluation tree, by calling recursively the callables,
	/// and evaluating the values and identifiers.
	/// \param expression The evaluation tree to evaluate.
	/// \param scope The variables currently defined in the calling scope.
	/// \returns The resulting value of the evaluation.
	Value evaluate(const EvaluationTree& expression, Scope& scope);

	/// Binds a value to an identifier in the current scope.
	/// \param expression The expression of the bind call, consisting of:
	/// * The "define" identifier;
	/// * The identifier that will be bound to the value;
	/// * The value to bind;
	/// \param scope The scope in which the value will be bound.
	/// \returns The bound value.
	Value define(const EvaluationTree& expression, Scope& scope);

	/// Conditionally evaluates parts of the expression.
	/// \param expression The expression of the conditional, consisting of:
	/// * The "if" identifier;
	/// * The condition, must be a boolean;
	/// * The value to evaluate if the condition is true;
	/// * Optionally, the value to evaluate if the condition is false;
	/// \param scope The scope in which the conditional will be evaluated
	/// \returns The first value if the condition is true, or the second
	/// value if the condition is false, or null is there is no second value.
	Value if_(const EvaluationTree& expression, Scope& scope);

	/// Binds a new user-defined function to the current scope.
	/// \param expression The expression of the user-defined function,
	/// consisting of:
	/// * The "function" identifier;
	/// * The identifier of the bound function;
	/// * A list of identifiers, representing the function parameters;
	/// * The body of the function.
	/// \param scope The scope in which the function will be defined. This
	/// scope is the one that will be available when the function will be
	/// evaluated.
	/// \returns The defined function, as a value.
	Value defineFunction(const EvaluationTree& expression, Scope& scope);
}

#endif // BUILTIN_CALLABLE_HPP
