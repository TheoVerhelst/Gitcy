#include "NodeEvaluator.hpp"

Data Interpreter::evaluateTree(const Tree<Interpreter::EvaluationNode>::Ptr& expression)
{
	Data res;
	switch(expression->getValue().type)
	{
		case EvaluationNode::Type::Call:
		{
			if(expression->numberChildren() == 0)
				return false;
			else
			{
				const Data& functionValue{evaluateTree(expression->getChild(0))};
				// Check that the first child is a function
				if(functionValue.type() != typeid(Function))
					throw ScriptError("First value in a function call is not a function (got type \"" + std::string(functionValue.type().name()) + "\")");

				const Function& function{boost::get<Function>(functionValue)};
				// Check that we have the right number of parameters
				if(function.getNumberOfParameters() > -1 and (expression->numberChildren() - 1) != static_cast<size_t>(function.getNumberOfParameters()))
				{
					throw ScriptError("wrong number of arguments" ", got "
							+ std::to_string(expression->numberChildren()) + " arguments " +
							"while expecting " + std::to_string(function.getNumberOfParameters()));
				}

				std::vector<Data> args;
				for(size_t i{1}; i < expression->numberChildren(); ++i)
					args.push_back(evaluateTree(expression->getChild(i)));
				res = function.getPointer()(args);
				break;
			}
		}

		case EvaluationNode::Type::Value:
			res = expression->getValue().value;
			break;

		case EvaluationNode::Type::Identifier:
		{
			const std::string& identifier(expression->getValue().name);
			auto it(m_variables.find(identifier));
			if(it == m_variables.end())
				throw ScriptError("Unknown variable: \"" + identifier + "\"");
			res = *(it->second);
		}
	}

	return res;
}
