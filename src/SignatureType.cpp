#include <Function.hpp>
#include <Utils.hpp>
#include <SignatureType.hpp>

const std::map<std::type_index, std::string> SignatureType::_typePrettyNames
{
	{typeid(int), "Integer"},
	{typeid(double), "Real"},
	{typeid(bool), "Boolean"},
	{typeid(std::string), "String"},
	{typeid(Function), "Function"}
};

std::ostream& operator<<(std::ostream& os, const SignatureType& signatureType)
{
	// If _typeIndex contains something
	if(signatureType._typeIndex)
		return os << SignatureType::_typePrettyNames.at(signatureType._typeIndex.value());
	else
		return os << "<any type>";
}

bool SignatureType::matches(const Data& data) const
{
	// If _typeIndex contains something
	if(_typeIndex)
		return std::type_index(data.type()) == _typeIndex.value();
	else
		return true;
}
