#include <sstream>
#include "Utils.hpp"
#include "ScriptError.hpp"
#include "Function.hpp"

Function::Function(const std::vector<Overload>& overloads):
	_overloads{overloads}
{
}

Data Function::operator()(const std::vector<Data>& arguments) const
{
	for(auto& overload : _overloads)
	{
		if(overload.matches(arguments))
			return overload(arguments);

	}

	throw ScriptError("No overload found for given arguments:\n"
			"Got      (" + Utils::toString(arguments) + ") while calling\n" +
			 Utils::toString(*this));
}

std::ostream& operator<<(std::ostream& os, const Function& function)
{
	return os << "<Function(" << Utils::join(" | ", function._overloads.begin(), function._overloads.end()) << ")>";
}

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values)
{
	return os << Utils::join(", ", values.begin(), values.end());
}
