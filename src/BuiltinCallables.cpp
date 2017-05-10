#include <Value.hpp>
#include <ScriptError.hpp>
#include <Function.hpp>
#include <Null.hpp>
#include <Scope.hpp>
#include <UserDefinedFunction.hpp>
#include <EvaluationTree.hpp>
#include <BuiltinCallables.hpp>

const Callable BuiltinCallables::evaluate{BuiltinCallables::_evaluate};
const Callable BuiltinCallables::define{BuiltinCallables::_define};
const Callable BuiltinCallables::if_{BuiltinCallables::_if};
const Callable BuiltinCallables::defineFunction{BuiltinCallables::_defineFunction};

Value BuiltinCallables::_evaluate(const EvaluationTree& expression, Scope& scope)
{
	const EvaluationNode node{expression.getNode()};
	if(node.type() == typeid(Call))
	{
		if(not expression.hasChildren())
			throw ScriptError("Call expression without any macro/function to call");

		// Evaluate the first child, it is the function/macro to call
		const Value& callable{evaluate(expression.getChild(0), scope)};

		// Check that the first child is a callable
		if(callable.holdsType<Callable>())
			return callable.get<Callable>()(expression, scope);
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
			throw ScriptError("Unknown identifier: \"" + identifier + "\"");
		}
	}
}

Value BuiltinCallables::_define(const EvaluationTree& expression, Scope& scope)
{
	if(expression.numberChildren() != 3)
		throw ScriptError("\"define\" must be called with two arguments");
	const EvaluationTree& identifierNode{expression.getChild(1)};
	const EvaluationTree& valueNode{expression.getChild(2)};
	if(identifierNode.getNode().type() != typeid(Identifier))
		throw ScriptError("The first argument to \"define\" must be an identifier.");

	const Identifier identifier{boost::get<Identifier>(identifierNode.getNode())};
	const Value value{evaluate(valueNode, scope)};
	scope.setVariable(identifier, value);
	return value;
}

Value BuiltinCallables::_if(const EvaluationTree& expression, Scope& scope)
{
	const std::size_t numberChildren{expression.numberChildren()};
	if(not (numberChildren == 3 or numberChildren == 4))
		throw ScriptError("\"if\" must be called with two or three arguments (got " + std::to_string(numberChildren) +")");
	const EvaluationTree& testNode{expression.getChild(1)};
	const EvaluationTree& ifBodyNode{expression.getChild(2)};

	// Evaluate the condition
	const Value testValue{evaluate(testNode, scope)};
	if(not testValue.holdsType<bool>())
		throw ScriptError("First argument of \"if\" must be a boolean value (got \"" + testValue.getTypeName() + "\")");

	// If the condition is met, then execute the if body
	if(testValue.get<bool>())
		return evaluate(ifBodyNode, scope);
	// Else, execute the else body only if it exists
	else if(expression.numberChildren() == 4)
		return evaluate(expression.getChild(3), scope);
	else
		return Null();
}

Value BuiltinCallables::_defineFunction(const EvaluationTree& expression, Scope& scope)
{
	if(expression.numberChildren() <= 3)
		throw ScriptError("\"function\" needs at least two arguments: an identifier and the function body");
	const auto identifierNode{expression.getChild(1)};
	if(identifierNode.getNode().type() != typeid(Identifier))
		throw ScriptError("First argument of \"function\" must be an identifier");

	const Identifier identifier{boost::get<Identifier>(identifierNode.getNode())};
	const Callable value{Function({std::make_shared<UserDefinedFunction>(expression, scope)})};
	scope.setVariable(identifier, Value(value));
	return value;
}
