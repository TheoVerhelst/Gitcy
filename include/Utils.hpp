#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <Data.hpp>

/// Various functions and classes that are not directly related to the project.
namespace Utils
{
	/// Returns a string that is the result of calling the output stream
	/// operator on a stream with each of the object in the sequence between
	/// \a begin and \a end, and with the given string separator between each
	/// insertion.
	/// \example
	/// \code
	/// std::vector<std::string> v{"one", "two", "three"};
	/// std::cout << Utils::join("|", v.begin(), v.end()); // outputs "one|two|three"
	/// \tparam InputIterator An input iterator which can be dereferrenced and
	/// outputed to a std::ostream.
	/// \param separator The string separator.
	/// \param begin The begin of the sequence to join.
	/// \param end The end of the sequence to join.
	/// \returns The joined string.
	template <typename InputIterator>
	std::string join(const std::string& separator, InputIterator begin, InputIterator end);

	/// Gives the string resulting of calling the output stream operator on a
	/// std::ostream with the object.
	/// \tparam T A type that overloads operator<<(std::ostream&, const T&).
	/// \param object The object to convert to string.
	template <typename T>
	std::string toString(const T& object);

	template <typename T>
	std::vector<T> convert(const std::vector<Data>& args);
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


	template <typename T>
	std::vector<T> convert(const std::vector<Data>& args)
	{
		std::vector<T> convertedArguments;
		std::transform(args.begin(), args.end(), std::back_inserter(convertedArguments),
				[](const Data& data)
				{
					return data.get<T>();
				});
		return convertedArguments;
	}
}

#endif // UTILS_HPP
