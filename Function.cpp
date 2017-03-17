#include "Function.hpp"

Function::Function(int numberOfParameters, std::function<Data(const std::vector<Data>&)> pointer):
	_numberOfParameters{numberOfParameters},
	_pointer{pointer}
{
}

int Function::getNumberOfParameters() const
{
	return _numberOfParameters;
}

const std::function<Data(const std::vector<Data>&)>& Function::getFunction() const
{
	return _pointer;
}

std::ostream& operator<<(std::ostream& os, const Function& function)
{
	return os << "<Function with " << function.getNumberOfParameters() << " parameters>";
}
