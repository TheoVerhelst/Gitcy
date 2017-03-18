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
	std::vector<std::string> overloadsStrings;
	for(auto& overload : function._overloads)
		overloadsStrings.push_back(Utils::toString(overload));

	return os << "<Function(" << Utils::join(" | ", overloadsStrings) << ")>";
}

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values)
{
	std::vector<std::string> valuesTypesStrings;
	for(auto& value : values)
		valuesTypesStrings.push_back(Utils::toString(SignatureType(value.type())));
	return os << Utils::join(", ", valuesTypesStrings);
}
