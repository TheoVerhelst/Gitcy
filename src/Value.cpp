#include <Value.hpp>

const std::map<std::type_index, std::string> Value::_typePrettyNames
{
	{typeid(int), "Integer"},
	{typeid(double), "Real"},
	{typeid(bool), "Boolean"},
	{typeid(std::string), "String"},
	{typeid(std::shared_ptr<Callable>), "Callable"}
};

bool Value::holdsType(const std::type_index& typeIndex) const
{
	return typeIndex == std::type_index(_variant.type());
}

std::string Value::getTypeName() const
{
	return _typePrettyNames.at(std::type_index(_variant.type()));
}

std::string Value::getTypeName(const std::type_index& typeIndex)
{
	auto it(_typePrettyNames.find(typeIndex));
	if(it != _typePrettyNames.end())
		return it->second;
	else
		throw std::invalid_argument("unrecognised type in Value::getTypeName (got \"" + std::string(typeIndex.name()) + "\")");
}

std::ostream& operator<<(std::ostream& os, const Value& data)
{
	return os << data._variant;
}
