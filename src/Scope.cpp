#include <Scope.hpp>

Scope::Scope(std::map<std::string, std::shared_ptr<Value>> variables):
	_variables{variables}
{
}

const Value& Scope::getVariable(const std::string& name) const
{
	return *_variables.at(name);
}

void Scope::setVariable(const std::string& name, const Value& newValue)
{
	_variables.at(name) = std::make_shared<Value>(newValue);
}

