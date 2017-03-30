#include <Utils.hpp>
#include <Function.hpp>
#include <Data.hpp>
#include <Overload.hpp>

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

bool Overload::isVariadic() const
{
	return _isVariadic;
}

Overload::Overload(const std::vector<SignatureType>& typeList, bool isVariadic):
	_typeList{typeList},
	_isVariadic{isVariadic}
{
}

std::ostream& operator<<(std::ostream& os, const Overload& overload)
{
	os << Utils::join(", ", overload._typeList.begin(), overload._typeList.end());
	if(overload._isVariadic)
		os << ", ...";
	return os;
}
