#include <sstream>
#include <algorithm>
#include <functional>
#include <Utils.hpp>
#include <ScriptError.hpp>
#include <Function.hpp>

Function::Function(const std::vector<Overload>& overloads):
	_overloads{overloads}
{
}

Data Function::operator()(const std::vector<Data>& arguments) const
{
	// Find the first overload that matches the arguments
	auto it(std::find_if(_overloads.begin(), _overloads.end(),
			std::bind(&Overload::matches, std::placeholders::_1, arguments)));
	// If a match has been found
	if(it != _overloads.end())
		return (*it)(arguments);
	else
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
