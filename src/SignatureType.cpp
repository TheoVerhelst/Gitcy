#include <SignatureType.hpp>

bool SignatureType::matches(const Data& data) const
{
	// If _typeIndex contains something
	if(_typeIndex)
		return std::type_index(data.getType()) == _typeIndex.value();
	else
		return true;
}

std::ostream& operator<<(std::ostream& os, const SignatureType& signatureType)
{
	// If _typeIndex contains something
	if(signatureType._typeIndex)
		return os << Data::getTypeName(signatureType._typeIndex.value());
	else
		return os << "<any type>";
}
