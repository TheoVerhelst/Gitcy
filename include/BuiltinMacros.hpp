#ifndef BUILTIN_MACROS_HPP
#define BUILTIN_MACROS_HPP

#include <Macro.hpp>

namespace BuiltinMacros
{
	class Evaluate : public Macro
	{
		public:
			/// Evaluates an evaluation tree, by calling recursively the functions
			/// or macro, and evaluating the values and identifiers.
			/// \param expression The evaluation tree to evaluate.
			/// \param scope The variables currently defined in the calling scope.
			/// \returns The resulting value of the evaluation.
			virtual Value call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope) override;
	};

	class Define : public Macro
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope) override;
	};

	class If : public Macro
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope) override;
	};

	class DefineFunction : public Macro
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope) override;
	};
}

#endif // BUILTIN_MACROS_HPP
