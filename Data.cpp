#include "Data.hpp"

std::ostream& operator<<(std::ostream& os, const Null& /* null */)
{
	return os << "null";
}
