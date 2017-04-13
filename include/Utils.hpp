#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <Value.hpp>

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
	std::vector<T> convert(const std::vector<Value>& args);

	/// This class allows to temporarily listen to all the output being sent to
	/// a std::ostream instance (such as std::cout or std::cerr), in order to
	/// programmatically read this output. This can be used to test output
	/// functions, for example.
	class OstreamListener
	{
		public:
			/// Constructor.
			/// \param listenedStream The stream to listen to.
			explicit OstreamListener(std::ostream& listenedStream);

			/// Destructor. Sets the listened stream to its initial state.
			~OstreamListener();

			/// Returns The output that has been sent to the listened stream so
			/// far.
			/// \returns The output that has been sent to the listened stream so
			/// far.
			std::string getOutput() const;

		private:
			std::ostream& _listenedStream;
			std::streambuf* _streamBuffer;
			std::ostringstream _localStream;
	};
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
	std::vector<T> convert(const std::vector<Value>& args)
	{
		std::vector<T> convertedArguments;
		std::transform(args.begin(), args.end(), std::back_inserter(convertedArguments),
				[](const Value& data)
				{
					return data.get<T>();
				});
		return convertedArguments;
	}
}

#endif // UTILS_HPP
