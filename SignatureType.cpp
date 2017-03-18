#include "Function.hpp"
#include "SignatureType.hpp"

const std::map<std::type_index, std::string> SignatureType::_typePrettyNames
{
	{typeid(int), "Integer"},
	{typeid(float), "Real"},
	{typeid(bool), "Boolean"},
	{typeid(std::string), "String"},
	{typeid(Function), "Function"}
};

SignatureType::SignatureType()
{
}

SignatureType::SignatureType(const std::type_info& type):
	_typeIndex{type}
{
}

std::string SignatureType::getName() const
{
	if(_typeIndex)
	{
		auto it(_typePrettyNames.find(_typeIndex.value()));
		if(it != _typePrettyNames.end())
			return it->second;
		else
			return _typeIndex.value().name();
	}
	else
		return "<any type>";
}

bool SignatureType::matches(const Data& data) const
{
	if(_typeIndex)
		return std::type_index(data.type()) == _typeIndex.value();
	else
		return true;
}
