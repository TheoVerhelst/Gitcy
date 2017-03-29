#include <Function.hpp>
#include <Data.hpp>

const std::map<std::type_index, std::string> Data::_typePrettyNames
{
	{typeid(int), "Integer"},
	{typeid(double), "Real"},
	{typeid(bool), "Boolean"},
	{typeid(std::string), "String"},
	{typeid(Function), "Function"}
};

bool Data::holdsType(const std::type_index& typeIndex) const
{
	return typeIndex == std::type_index(_variant.type());
}

std::string Data::getTypeName() const
{
	return _typePrettyNames.at(std::type_index(_variant.type()));
}

std::string Data::getTypeName(const std::type_index& typeIndex)
{
	auto it(_typePrettyNames.find(typeIndex));
	if(it != _typePrettyNames.end())
		return it->second;
	else
		throw std::invalid_argument("unrecognised type in Data::getTypeName (got \"" + std::string(typeIndex.name()) + "\")");
}

std::ostream& operator<<(std::ostream& os, const Data& data)
{
	return os << data._variant;
}
