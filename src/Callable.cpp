#include <Value.hpp>
#include <Function.hpp>
#include <Callable.hpp>
#include <ValueTypes.hpp>

std::ostream& operator<<(std::ostream& os, const Callable& callable)
{
	return os << ValueTypes::getTypeName(std::type_index(typeid(callable)));
}
