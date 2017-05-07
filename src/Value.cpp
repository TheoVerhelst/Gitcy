#include <ValueTypes.hpp>
#include <Value.hpp>

bool Value::holdsType(const std::type_index& typeIndex) const
{
	return typeIndex == std::type_index(_value.type());
}

std::string Value::getTypeName() const
{
	return ValueTypes::getTypeName(std::type_index(_value.type()));
}

std::ostream& operator<<(std::ostream& os, const Value& data)
{
	return os << data._value;
}
