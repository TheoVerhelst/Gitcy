#include <ValueTypes.hpp>
#include <Value.hpp>

bool Value::holdsType(const std::type_index& typeIndex) const
{
	return typeIndex == std::type_index(boost::type_erasure::typeid_of(_value));
}

std::string Value::getTypeName() const
{
	return ValueTypes::getTypeName(std::type_index(boost::type_erasure::typeid_of(_value)));
}

std::ostream& operator<<(std::ostream& os, const Value& data)
{
	return os << data._value;
}
