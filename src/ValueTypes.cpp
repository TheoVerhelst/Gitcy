#include <ValueTypes.hpp>
#include <Callable.hpp>

const std::map<std::type_index, std::string> ValueTypes::_typeNames
{
	{typeid(int), "Integer"},
	{typeid(double), "Real"},
	{typeid(bool), "Boolean"},
	{typeid(std::string), "String"},
	{typeid(Callable), "Callable"}
};

std::string ValueTypes::getTypeName(const std::type_index& typeIndex)
{
	auto it(_typeNames.find(typeIndex));
	if(it != _typeNames.end())
		return it->second;
	else
		return typeIndex.name();
}

const std::type_index& ValueTypes::getTypeIndex(const std::string& typeName)
{
	for(auto& pair : _typeNames)
		if(pair.second == typeName)
			return pair.first;
	throw std::invalid_argument("Provided type name does not match to any type: \"" + typeName + "\"");
}
