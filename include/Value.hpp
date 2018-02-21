#ifndef VALUE_HPP
#define VALUE_HPP

#include <ostream>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <ValueBadGet.hpp>
#include <ValueImpl.hpp>

/// The type used in C++ to represent any value in script. A Value can store
/// multiple types, but one instance can only contain one value of one type at a
/// time, just like boost::any (or std::any).
class Value
{
	public:
		Value(const Value& other);

		Value(Value&& other);

		/// Constructor.
		/// \param value The value that will be held.
		/// \tparam T The type of the value that will be held.
		template <typename T, typename = std::enable_if_t<not std::is_same<std::decay_t<T>, Value>::value>>
		Value(T value);

		Value& operator=(Value other);

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

		friend void swap(Value& lhs, Value& rhs);

		/// Overload of the output operator.
		/// \param os The stream to output to.
		/// \param null The Value object to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Value& data);

	private:
		std::unique_ptr<ValueImplBase> _value;
};

template <typename T, typename>
Value::Value(T value):
	_value{new ValueImpl<T>{std::move(value)}}
{
}

template <typename T>
const T& Value::get() const
{
	if(holdsType<T>())
		return static_cast<ValueImpl<T>*>(_value.get())->getValue();
	else
		throw ValueBadGet("Bad Value::get<T> with T="
				+ std::string(typeid(T).name())
				+ " while storing type "
				+ std::string(_value->type().name()));
}

template <typename T>
bool Value::holdsType() const
{
	return _value->type() == typeid(T);
}

#endif // VALUE_HPP
