#include "Utils.hpp"

std::string Utils::join(const std::string& middle, const std::vector<std::string>& strings)
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
