#ifndef BUILTIN_CALLABLE_HPP
#define BUILTIN_CALLABLE_HPP

#include <Callable.hpp>

namespace BuiltinCallables
{
	/// Evaluates an evaluation tree, by calling recursively the callables,
	/// and evaluating the values and identifiers.
	/// \param expression The evaluation tree to evaluate.
	/// \param scope The variables currently defined in the calling scope.
	/// \returns The resulting value of the evaluation.
	Value evaluate(const EvaluationTree& expression, Scope& scope);

	Value define(const EvaluationTree& expression, Scope& scope);
	
	Value if_(const EvaluationTree& expression, Scope& scope);

	Value defineFunction(const EvaluationTree& expression, Scope& scope);
}

#endif // BUILTIN_CALLABLE_HPP
