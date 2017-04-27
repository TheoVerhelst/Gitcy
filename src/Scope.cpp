#include <Value.hpp>
#include <Scope.hpp>

Scope::Scope(const std::map<std::string, std::shared_ptr<Value>>& variables):
	_variables{variables}
{
}

const Value& Scope::getVariable(const std::string& identifier) const
{
	return *_variables.at(identifier);
}

void Scope::setVariable(const std::string& identifier, const Value& value)
{
	_variables[identifier] = std::make_shared<Value>(value);
}
