#include <BuiltinCallables.hpp>
#include <Scope.hpp>
#include <EvaluationTree.hpp>
#include <UserDefinedFunction.hpp>

UserDefinedFunction::UserDefinedFunction(const EvaluationTree& functionBody, Scope& scope):
	Overload{generateSignature(functionBody), false},
	_functionBody{functionBody},
	_scope{scope},
	_parameterNames{generateParameterNames(functionBody)}
{
}

Value UserDefinedFunction::call(const std::vector<Value>& arguments) const
{
	// Make a local copy of the scope
	Scope localScope{_scope};
	// Add the arguments as local variables. We should have the same
	// number of arguments and parameter names, since Function::call
	// already checked this.
	for(std::size_t i{0}; i < arguments.size(); ++i)
		localScope.setVariable(_parameterNames.at(i), arguments[i]);
	// Skip the "function" call identifier, the user-defined function identifier
	// and the parameter identifiers
	Value lastValue{Null()};
	for(std::size_t i{2 + _parameterNames.size()}; i < _functionBody.numberChildren(); ++i)
		// Evaluate each part of the body of the function
		lastValue = BuiltinCallables::evaluate(_functionBody.getChild(i), localScope);
	return lastValue;
}
		
std::vector<SignatureType> UserDefinedFunction::generateSignature(const EvaluationTree& functionBody)
{
	// Since generateParameterNames already parses the beginning of the body
	// by looking for the first identifier, we can reuse its result
	return std::vector<SignatureType>(generateParameterNames(functionBody).size(), SignatureType::create());
}

std::vector<std::string> UserDefinedFunction::generateParameterNames(const EvaluationTree& functionBody)
{
	std::vector<std::string> result;
	// Skip the "function" call identifier and the user-defined function identifier
	for(std::size_t i{2}; i < functionBody.numberChildren(); ++i)
	{
		const auto& nodeValue(functionBody.getChild(i).getNode());
		if(nodeValue.type() == typeid(Identifier))
			result.push_back(boost::get<Identifier>(nodeValue));
		else
			return result;
	}
	return result;
}
