#include <BuiltinCallables.hpp>
#include <Scope.hpp>
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
	return BuiltinCallables::Evaluate().call(_functionBody, localScope);
}
		
std::vector<SignatureType> UserDefinedFunction::generateSignature(const EvaluationTree& functionBody)
{
	// Since generateParameterNames already parses the beginning of the body
	// by looking for the first identifier, we can reuse its result
	return std::vector<SignatureType>(generateParameterNames(functionBody).size(), SignatureType::create());
}

std::vector<Identifier> UserDefinedFunction::generateParameterNames(const EvaluationTree& functionBody)
{
	std::vector<Identifier> result;
	// The first node is the function identifier, we have to skip it, it is not
	// part of the argument list
	// TODO find better
	bool functionIdentifierSkipped{false};
	for(auto& node : functionBody)
	{
		if(not functionIdentifierSkipped)
		{
			functionIdentifierSkipped = true;
			continue;
		}
		if(node.getValue().type() == typeid(Identifier))
			result.push_back(boost::get<Identifier>(node.getValue()));
		else
			return result;
	}
	return result;
}
