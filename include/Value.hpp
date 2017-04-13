#ifndef VALUE_HPP
#define VALUE_HPP

#include <ostream>
#include <string>
#include <map>
#include <typeindex>
#include <boost/variant.hpp>
#include <boost/mpl/contains.hpp>
#include <Null.hpp>

// Forward declarations
class Callable;

/// The type used in C++ to represent any value in script. It uses internally
/// a boost::variant, but exposes only the needed interface.
class Value
{
	public:
		/// Constructor.
		template <typename T, typename = std::enable_if_t<std::negation<std::is_same<std::decay_t<T>, Value>>::value>>
		Value(T value);

		template <typename T>
		const T& get() const;

		template <typename T>
		bool holdsType() const;

		bool holdsType(const std::type_index& typeIndex) const;

		template <typename T>
		static constexpr bool canHoldType();

		std::string getTypeName() const;

		static std::string getTypeName(const std::type_index& typeIndex);

		/// Overload of the output operator.
		/// \param os The stream to output to.
		/// \param null The Value object to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Value& data);

	private:
		typedef boost::variant<Null, bool, int, double, std::string, boost::recursive_wrapper<std::shared_ptr<Callable>>> Variant;

		/// Actual variant.
		Variant _variant;

		/// Map of pretty names for types to display in the output operator.
		static const std::map<std::type_index, std::string> _typePrettyNames;
};

#include <Callable.hpp>

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
