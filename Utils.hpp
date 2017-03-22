#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <sstream>
#include <memory>
#include <boost/mpl/for_each.hpp>
#include <boost/type.hpp>

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

	/// Class that checks whether the template MPL type sequence contains the
	/// type given in the constructor. The magic of this class is that it loops
	/// over the static sequence at runtime, and searches for the given runtime
	/// type info.
	///
	/// Once an object of this class is constructed, the value method indicates
	/// if the given type is present in the template type sequence.
	///
	/// \tparam TypeSequence a MPL Sequence (see
	/// http://www.boost.org/doc/libs/1_63_0/libs/mpl/doc/refmanual/forward-sequence.html )
	template <typename TypeSequence>
	class RuntimeContains
	{
		public:
			/// Constructor.
			/// \param typeIndex Runtime type info to search for.
			RuntimeContains(const std::type_index& typeIndex);

			/// Indicates whether the type given to the constructor is present
			/// in the template type sequence.
			/// \returns True if the type given to the constructor is present
			/// in the template type sequence, false otherwhise.
			bool value() const;

		private:
			/// Call operator used internally in the boost::mpl::for_loop.
			/// Sets to true _found if the type T is the same as the one given
			/// to the constructor.
			/// \tparam T A type to check.
			/// \param An instance of the boost::type wrapper, it allows to not
			/// construct an object of type T, but rather an instance of this
			/// wrapper (which contains nothing). We need it because
			/// boost::mpl::for_each call this operator with actual instances.
			template <typename T>
			void operator()(boost::type<T>);

			/// Indicates whether the type given to the constructor is present
			/// in the template type sequence.
			std::shared_ptr<bool> _found;

			/// The type to search for, stored as a runtime type info.
			const std::type_index& _typeIndex;
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

	template <typename TypeSequence>
	RuntimeContains<TypeSequence>::RuntimeContains(const std::type_index& typeIndex):
	_found{std::make_shared<bool>(false)},
	_typeIndex{typeIndex}
	{
		// Call operator() on a copy of this object for every type in TypeSequence,
		// the second argument is a simple wrapper that avoid to default-construct objects
		// of the types in TypeSequence.
		boost::mpl::for_each<TypeSequence, boost::type<boost::mpl::_>>(*this);
	}

	template <typename TypeSequence>
	bool RuntimeContains<TypeSequence>::value() const
	{
		return *_found;
	}

	template <typename TypeSequence>
	template <typename T>
	void RuntimeContains<TypeSequence>::operator()(boost::type<T>)
	{
		if(not *_found)
			*_found = std::type_index(typeid(T)) == _typeIndex;
	}

}

#endif // UTILS_HPP
