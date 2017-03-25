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

const std::type_info& Data::getType() const
{
	return _variant.type();
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
		throw std::invalid_argument("unrecognized type in Data::getTypeName (got \"" + std::string(typeIndex.name()));
}

std::ostream& operator<<(std::ostream& os, const Data& data)
{
	return os << data._variant;
}
