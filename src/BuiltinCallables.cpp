#include <Value.hpp>
#include <ScriptError.hpp>
#include <BuiltinCallables.hpp>

namespace BuiltinCallables
{
	Value Evaluate::call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope)
	{
		const EvaluationNode node{expression->getValue()};
		if(node.type() == typeid(Call))
		{
			if(not expression->hasChildren())
				throw ScriptError("Call expression without macro/function to call");

			// Evaluate the first child, it is the function/macro to call
			const Value& callable{call(*expression->begin(), scope)};

			// Check that the first child is a callable
			if(callable.holdsType<std::shared_ptr<Callable>>())
				return callable.get<std::shared_ptr<Callable>>()->call(expression, scope);
			else
				throw ScriptError("Call expression on non-callable value (got type \"" + callable.getTypeName() + "\")");
		}
		else if(node.type() == typeid(Value))
			return boost::get<Value>(node);
		else // Identifier
		{
			const Identifier identifier{boost::get<Identifier>(node)};
			try
			{
				return scope.getVariable(identifier);
			}
			catch(const std::out_of_range& e)
			{
				throw ScriptError("Unknown variable: \"" + identifier + "\"");
			}
		}
	}

	Value Define::call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope)
	{
		return true;
	}

	Value If::call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope)
	{
		return true;
	}

	Value DefineFunction::call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope)
	{
		return true;
	}
}
