#include <SignatureType.hpp>

bool SignatureType::matches(const Value& data) const
{
	// If _typeIndex contains something
	if(_typeIndex)
		return data.holdsType(_typeIndex.value());
	else
		return true;
}

std::ostream& operator<<(std::ostream& os, const SignatureType& signatureType)
{
	// If _typeIndex contains something
	if(signatureType._typeIndex)
		return os << Value::getTypeName(signatureType._typeIndex.value());
	else
		return os << "<any type>";
}
