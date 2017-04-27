#ifndef VALUE_HPP
#define VALUE_HPP

#include <ostream>
#include <string>
#include <map>
#include <typeindex>
#include <boost/variant.hpp>
#include <boost/mpl/contains.hpp>
#include <Null.hpp>
#include <Callable.hpp>

/// The type used in C++ to represent any value in script. It uses internally
/// a boost::variant, but exposes only the needed interface. A Value can store
/// multiple type (Null, bool, int, double, std::string and Callable), but
/// one instance can only contain one value of one type at a time, just like
/// boost::variant (or std::variant).
class Value
{
	public:
		/// Constructor.
		/// \tparam T The type that will be held internally.
		template <typename T, typename = std::enable_if_t<std::negation<std::is_same<std::decay_t<T>, Value>>::value>>
		Value(T value);

		/// Gets the value with type T. A static check is done at compile time
		/// to ensure that T is one of the types supported by Value, and another
		/// check is done a run time to ensure that T is the type effectively
		/// held.
		/// \tparam T The type supposed to be held by this instance.
		/// \returns The held value.
		/// \throws boost::bad_get if this instance does not hold a value of
		/// type T.
		template <typename T>
		const T& get() const;

		/// Checks whether this instance holds the type T. A compile-time check
		/// is done to ensure that T is one of the supported types. To check
		/// whether an instance could contain an arbitrary type, see
		/// canHoldType.
		/// \tparam T The type to check
		/// \returns true if this instance holds a value of type T.
		template <typename T>
		bool holdsType() const;

		/// Checks whether this instance holds the type represented by
		/// typeIndex. To check whether an instance could contain an arbitrary
		/// type, see canHoldType. A std::type_index can be created as:
		/// \code
		/// value.holdsType(std::type_index(typeid(int)));
		/// \endcode
		/// \param typeIndex The type to check.
		/// \returns true if this instance holds a value of type typeIndex,
		/// false otherwise.
		bool holdsType(const std::type_index& typeIndex) const;

		/// Checks whether T is one of the supported types.
		/// \tparam T The type to check
		/// \returns true if T is one of the supported types, false otherwise.
		template <typename T>
		static constexpr bool canHoldType();

		/// Returns a fancy name of the type currently held by this instance.
		/// \returns The type name.
		std::string getTypeName() const;

		/// Returns a fancy name of the supplied type.
		/// \param typeIndex The type to check.
		/// \returns The type name.
		static std::string getTypeName(const std::type_index& typeIndex);

		/// Overload of the output operator.
		/// \param os The stream to output to.
		/// \param null The Value object to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Value& data);

	private:
		/// The internal type of the value.
		typedef boost::variant<Null, bool, int, double, std::string, boost::recursive_wrapper<Callable>> Variant;

		/// Actual variant.
		Variant _variant;

		/// Map of pretty names for types to display in the output operator.
		static const std::map<std::type_index, std::string> _typePrettyNames;
};

template <typename T, typename>
Value::Value(T value):
	_variant{std::forward<T>(value)}
{
}

template <typename T>
const T& Value::get() const
{
	return boost::get<T>(_variant);
}

template <typename T>
bool Value::holdsType() const
{
	// Statically checks if T is in the Variant types
	static_assert(canHoldType<T>(), "T is not in the Variant types");
	return _variant.type() == typeid(T);
}

template <typename T>
constexpr bool Value::canHoldType()
{
	return boost::mpl::contains<Variant::types, T>::value;
}

#endif // VALUE_HPP
