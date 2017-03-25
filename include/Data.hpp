#ifndef DATA_HPP
#define DATA_HPP

#include <ostream>
#include <string>
#include <map>
#include <typeindex>
#include <boost/variant.hpp>
#include <boost/mpl/contains.hpp>
#include <Null.hpp>

// Forward declaration
class Function;

/// The type used in C++ to represent any value in script. It uses internally
/// a boost::variant, but exposes only the needed interface.
/// \TODO Rename to value?
class Data
{
	public:
		/// Constructor.
		template <typename T, typename = std::enable_if_t<std::negation<std::is_same<std::decay_t<T>, Data>>::value>>
		Data(T value);

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
		/// \param null The Data object to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Data& data);

	private:
		typedef boost::variant<Null, bool, int, double, std::string, boost::recursive_wrapper<Function>> Variant;

		/// Actual variant.
		Variant _variant;

		/// Map of pretty names for types to display in the output operator.
		static const std::map<std::type_index, std::string> _typePrettyNames;
};

template <typename T, typename>
Data::Data(T value):
	_variant{std::forward<T>(value)}
{
}

template <typename T>
const T& Data::get() const
{
	return boost::get<T>(_variant);
}

template <typename T>
bool Data::holdsType() const
{
	// Statically checks if T is in the Variant types
	if(not canHoldType<T>())
		return false;
	else
		return _variant.type() == typeid(T);
}

template <typename T>
constexpr bool Data::canHoldType()
{
	return boost::mpl::contains<Variant::types, T>::value;
}

#endif // DATA_HPP
