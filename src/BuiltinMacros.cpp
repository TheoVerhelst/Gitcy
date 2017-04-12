#include <Value.hpp>
#include <ScriptError.hpp>
#include <BuiltinMacros.hpp>

namespace BuiltinMacros
{
	Value Evaluate::call(const Tree<EvaluationNode>::Ptr& expression, const Scope& scope)
	{
		const EvaluationNode node{expression->getValue()};
		if(node.type() == typeid(FunctionCall))
		{
			if(not expression->hasChildren())
				throw ScriptError("Call expression without macro/function to call");

			// Evaluate the first child, it is the function/macro to call
			const Value& functionData{call(*expression->begin(), scope)};

			// Check that the first child is a function
			if(functionData.holdsType<Function>())
			{
				const Function& function{functionData.get<Function>()};
				std::vector<Value> args;
				// Loop over the children from the second child to the last one
				for(auto it(std::next(expression->begin())); it != expression->end(); ++it)
					args.push_back(call(*it, scope));

				return function.call(args);
			}
			else if(functionData.holdsType<std::shared_ptr<Macro>>())
				return functionData.get<std::shared_ptr<Macro>>()->call(expression, scope);
			else
				throw ScriptError("Call expression on non-callable value (got type \"" + functionData.getTypeName() + "\")");
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
