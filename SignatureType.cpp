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

std::ostream& operator<<(std::ostream& os, const SignatureType& signatureType)
{
	if(signatureType._typeIndex)
	{
		auto it(SignatureType::_typePrettyNames.find(signatureType._typeIndex.value()));
		if(it != SignatureType::_typePrettyNames.end())
			return os << it->second;
		else
			return os << signatureType._typeIndex.value().name();
	}
	else
		return os << "<any type>";
}

bool SignatureType::matches(const Data& data) const
{
	if(_typeIndex)
		return std::type_index(data.type()) == _typeIndex.value();
	else
		return true;
}
