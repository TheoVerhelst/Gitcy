#ifndef BUILTIN_CALLABLE_HPP
#define BUILTIN_CALLABLE_HPP

#include <Callable.hpp>

namespace BuiltinCallables
{
	class Evaluate : public Callable
	{
		public:
			/// Evaluates an evaluation tree, by calling recursively the callables,
			/// and evaluating the values and identifiers.
			/// \param expression The evaluation tree to evaluate.
			/// \param scope The variables currently defined in the calling scope.
			/// \returns The resulting value of the evaluation.
			virtual Value call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope) override;
	};

	class Define : public Callable
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope) override;
	};

	class If : public Callable
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope) override;
	};

	class DefineFunction : public Callable
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope) override;
	};
}

#endif // BUILTIN_CALLABLE_HPP
