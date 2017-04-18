#include <Value.hpp>
#include <Function.hpp>
#include <Callable.hpp>

std::ostream& operator<<(std::ostream& os, const Callable& callable)
{
	return os << Value::getTypeName(std::type_index(typeid(callable)));
}