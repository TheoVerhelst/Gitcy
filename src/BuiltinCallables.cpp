#include <Value.hpp>
#include <ScriptError.hpp>
#include <BuiltinCallables.hpp>
#include <iostream>

namespace BuiltinCallables
{
	Value Evaluate::call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope)
	{
		const EvaluationNode node{expression->getValue()};
		if(node.type() == typeid(Call))
		{
			if(not expression->hasChildren())
				throw ScriptError("Call expression without any macro/function to call");

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

	Value Define::call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope)
	{
		auto identifierIterator(std::next(expression->begin()));
		if(expression->numberChildren() != 3 or (*identifierIterator)->getValue().type() != typeid(Identifier))
			throw ScriptError("define must be called with two arguments, the first one being an identifier.");
		const Identifier identifier{boost::get<Identifier>((*identifierIterator)->getValue())};
		const Value value{Evaluate().call(*std::next(identifierIterator), scope)};
		scope.setVariable(identifier, value);
		return value;
	}

	Value If::call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope)
	{
		return true;
	}

	Value DefineFunction::call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope)
	{
		return true;
	}
}
