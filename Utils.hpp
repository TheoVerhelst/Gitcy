#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>

namespace Utils
{
	template <typename InputIterator>
	std::string join(const std::string& separator, InputIterator begin, InputIterator end);

	template <typename T>
	std::string toString(const T& object);
}

namespace Utils
{

	template <typename InputIterator>
	std::string join(const std::string& separator, InputIterator begin, InputIterator end)
	{
		std::stringstream stream;
		stream << std::boolalpha;
		while(begin != end)
		{
			stream << *begin;
			if(++begin != end)
				stream << separator;

		}
		return stream.str();
	}

	template <typename T>
	std::string toString(const T& object)
	{
		std::stringstream stream;
		stream << std::boolalpha << object;
		return stream.str();
	}
}

#endif // UTILS_HPP
