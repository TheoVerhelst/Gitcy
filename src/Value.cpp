#include <ValueTypes.hpp>
#include <Value.hpp>

Value::Value(const Value& other):
	_value{other._value->clone()}
{
}

Value::Value(Value&& other)
{
	swap(*this, other);
}

Value& Value::operator=(Value other)
{
	swap(*this, other);
	return *this;
}

bool Value::holdsType(const std::type_index& typeIndex) const
{
	return typeIndex == std::type_index(_value->type());
}

std::string Value::getTypeName() const
{
	return ValueTypes::getTypeName(std::type_index(_value->type()));
}

void swap(Value& lhs, Value& rhs)
{
	using std::swap;
	swap(lhs._value, rhs._value);
}

std::ostream& operator<<(std::ostream& os, const Value& data)
{
	data._value->print(os);
	return os;
}
