#ifndef VALUE_HPP
#define VALUE_HPP

#include <ostream>
#include <typeindex>
#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/any_cast.hpp>
#include <boost/type_erasure/builtin.hpp>
#include <boost/type_erasure/operators.hpp>
#include <ValueBadGet.hpp>

/// The type used in C++ to represent any value in script. It uses internally
/// a boost class, and exposes only the needed interface. A Value can store
/// multiple types, but one instance can only contain one value of one type at a
/// time, just like boost::any (or std::any).
class Value
{
	public:
		/// Constructor.
		/// \tparam T The type that will be held internally.
		/// \TODO another overload taking const T& ?
		template <typename T, typename = std::enable_if_t<std::negation<std::is_same<std::decay_t<T>, Value>>::value>>
		Value(T value);

		/// Gets the value with type T.
		/// \tparam T The type supposed to be held by this instance.
		/// \returns The held value.
		/// \throws ValueBadGet if this instance does not hold a value of type
		/// T.
		template <typename T>
		const T& get() const;

		/// Checks whether this instance holds the type T.
		/// \tparam T The type to check
		/// \returns true if this instance holds a value of type T.
		template <typename T>
		bool holdsType() const;

		/// Checks whether this instance holds the type represented by
		/// typeIndex. A std::type_index can be created as:
		/// \code
		/// value.holdsType(std::type_index(typeid(int)));
		/// \endcode
		/// \param typeIndex The type to check.
		/// \returns true if this instance holds a value of type typeIndex,
		/// false otherwise.
		bool holdsType(const std::type_index& typeIndex) const;

		/// Returns a fancy name of the type currently held by this instance.
		/// \returns The type name.
		std::string getTypeName() const;

		/// Overload of the output operator.
		/// \param os The stream to output to.
		/// \param null The Value object to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Value& data);

	private:
		/// Actual variant.
		boost::type_erasure::any<
			boost::mpl::vector<
				boost::type_erasure::copy_constructible<>,
				boost::type_erasure::assignable<>,
				boost::type_erasure::typeid_<>,
				boost::type_erasure::ostreamable<>
		>> _value;
};

template <typename T, typename>
Value::Value(T value):
	_value{std::forward<T>(value)}
{
}

template <typename T>
const T& Value::get() const
{
	try
	{
		return boost::type_erasure::any_cast<const T&>(_value);
	}
	catch(const boost::type_erasure::bad_any_cast& e)
	{
		throw ValueBadGet(e.what());
	}
}

template <typename T>
bool Value::holdsType() const
{
	return boost::type_erasure::typeid_of(_value) == typeid(T);
}

#endif // VALUE_HPP
