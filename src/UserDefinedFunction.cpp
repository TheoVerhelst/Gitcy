#include <BuiltinCallables.hpp>
#include <Scope.hpp>
#include <Null.hpp>
#include <EvaluationTree.hpp>
#include <UserDefinedFunction.hpp>

UserDefinedFunction::UserDefinedFunction(const std::vector<Identifier> parameters,
		const EvaluationTree& functionBody, Scope& scope):
	Overload{std::vector<SignatureType>(parameters.size(), SignatureType::create()), false},
	_functionBody{functionBody},
	_scope{scope},
	_parameters{parameters}
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
		localScope.setVariable(_parameters.at(i), arguments[i]);

	return BuiltinCallables::evaluate(_functionBody, localScope);
}
