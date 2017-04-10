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
			/// \param variables The variables currently defined.
			/// \returns The resulting value of the evaluation.
			virtual Value call(const Tree<EvaluationNode>::Ptr& expression, std::map<std::string, std::shared_ptr<Value>>& variables) override;
	};

	class Define : public Macro
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& tree, std::map<std::string, std::shared_ptr<Value>>& variables) override;
	};

	class If : public Macro
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& tree, std::map<std::string, std::shared_ptr<Value>>& variables) override;
	};

	class DefineFunction : public Macro
	{
		public:
			Value call(const Tree<EvaluationNode>::Ptr& tree, std::map<std::string, std::shared_ptr<Value>>& variables) override;
	};
}

#endif // BUILTIN_MACROS_HPP
