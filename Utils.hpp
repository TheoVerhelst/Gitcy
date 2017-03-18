#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>

namespace Utils
{
	std::string join(const std::string& middle, const std::vector<std::string>& strings);
	template <typename T>
	std::string toString(const T& object);
}

namespace Utils
{
	template <typename T>
	std::string toString(const T& object)
	{
		std::stringstream stream;
		stream << object;
		return stream.str();
	}
}

#endif // UTILS_HPP
