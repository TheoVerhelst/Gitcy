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

	std::stringstream errorMessage;
	errorMessage << "No overload found for given arguments." << std::endl;
	errorMessage << "Got (" << arguments << ")" << std::endl;
	errorMessage << "while calling " << *this;
	throw ScriptError(errorMessage.str());
}

std::ostream& operator<<(std::ostream& os, const Function& function)
{
	std::vector<std::string> overloadsStrings;
	for(auto& overload : function._overloads)
	{
		std::stringstream sstream;
		sstream << overload;
		overloadsStrings.push_back(sstream.str());
	}
	return os << "<Function(" << Utils::join(" | ", overloadsStrings) << ")>";
}

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values)
{
	std::vector<std::string> valuesTypesStrings;
	for(auto& value : values)
		valuesTypesStrings.push_back(SignatureType(value.type()).getName());
	return os << Utils::join(", ", valuesTypesStrings);
}
