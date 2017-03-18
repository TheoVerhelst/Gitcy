#include <sstream>
#include "ScriptError.hpp"
#include "Function.hpp"


const std::map<std::type_index, std::string> SignatureType::_typePrettyNames
{
	{typeid(int), "Integer"},
	{typeid(float), "Real"},
	{typeid(bool), "Boolean"},
	{typeid(std::string), "String"},
	{typeid(Function), "Function"}
};

SignatureType::SignatureType()
{
}

SignatureType::SignatureType(const std::type_info& type):
	_typeIndex{type}
{
}

std::string SignatureType::getName() const
{
	if(_typeIndex)
	{
		auto it(_typePrettyNames.find(_typeIndex.value()));
		if(it != _typePrettyNames.end())
			return it->second;
		else
			return _typeIndex.value().name();
	}
	else
		return "<any type>";
}

bool SignatureType::matches(const Data& data) const
{
	if(_typeIndex)
		return std::type_index(data.type()) == _typeIndex.value();
	else
		return true;
}

Overload::Overload(const std::vector<SignatureType>& typeList, bool isVariadic, const Functor& functor):
	_typeList{typeList},
	_isVariadic{isVariadic},
	_functor{functor}
{
}

bool Overload::matches(const std::vector<Data>& arguments) const
{
	if(arguments.size() < _typeList.size() or (not _isVariadic and arguments.size() != _typeList.size()))
		return false;

	bool match{true};
	for(size_t i{0}; i < arguments.size() and match; ++i)
	{
		// If we are not yet in the variadic part
		if(i < _typeList.size())
			match =  _typeList[i].matches(arguments[i]);
		// Else, we are in the variadic part (ensured by the first test above)
		// Then if the type list is empty, we accept any type, so we can stop now
		else if(_typeList.empty())
			break;
		// Else, the variadic arguments must match the last type in the type list
		else
			match = _typeList.back().matches(arguments[i]);

	}
	return match;
}

Data Overload::operator()(const std::vector<Data>& arguments) const
{
	return _functor(arguments);
}

std::ostream& operator<<(std::ostream& os, const Overload& signature)
{
	std::vector<std::string> typesStrings;
	for(auto& type : signature._typeList)
		typesStrings.push_back(type.getName());

	os << join(", ", typesStrings);
	if(signature._isVariadic)
		os << ", ...";
	return os;
}

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
	return os << "<Function(" << join(" | ", overloadsStrings) << ")>";
}

std::ostream& operator<<(std::ostream& os, const std::vector<Data>& values)
{
	std::vector<std::string> valuesTypesStrings;
	for(auto& value : values)
		valuesTypesStrings.push_back(SignatureType(value.type()).getName());
	return os << join(", ", valuesTypesStrings);
}

std::string join(const std::string& middle, const std::vector<std::string>& strings)
{
	std::string res;
	for(size_t i{0}; i < strings.size(); ++i)
	{
		res += strings[i];
		if(i < strings.size() - 1)
			res += middle;
	}
	return res;
}
