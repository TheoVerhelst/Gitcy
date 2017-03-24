#ifndef SIGNATURE_TYPE_HPP
#define SIGNATURE_TYPE_HPP

#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <experimental/optional>
#include <boost/mpl/contains.hpp>
#include <Data.hpp>

/// A parameter type in an overload. If it is default-constructed, then that
/// represents no restriction on the parameter type. If the second constructor
/// is used, then that parameter must have a type that match the type given to
/// the constructor.
///
/// Objects of this class are compared to effective arguments passed to a script
/// function, and it is the responsability of this class to tell whether an
/// argument matches the parameter type.
class SignatureType
{
	public:
		/// Creates a SignatureType object representing the specified type.
		/// This function is used instead of the constructor because we cannot
		/// write a template constructor without argument.
		/// \tparam If given, either void (for no type restriction) or one of Data::types.
		/// \returns An object matching the given type \a T.
		template <typename T = void>
		static SignatureType create();

		/// Checks whether the given argument matches this object.
		/// \param data The argument to compare.
		/// \returns True if the given argument matches this object, false
		/// otherwise.
		bool matches(const Data& data) const;

		/// Overload of the stream output operator. It display nice names for
		/// types, such as "Integer", "String", etc...
		/// \param os The stream to output to.
		/// \param signatureType The object to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const SignatureType& signatureType);

	private:
		/// Default constructor. The public construction is done by the \a
		/// create method.
		SignatureType() = default;

		/// The type to match, if any. We use the optional class in the case we
		/// match any type.
		std::experimental::optional<std::type_index> _typeIndex;

		/// Map of pretty names for types to display in the output operator.
		static const std::map<std::type_index, std::string> _typePrettyNames;
};

template <typename T>
SignatureType SignatureType::create()
{
	// Assert that T is either void or one of Data::types
	static_assert(std::disjunction<std::is_void<T>, boost::mpl::contains<Data::types, T>>::value, "type T  must be one of Data::types.");

	SignatureType res;
	if(not std::is_void<T>::value)
		res._typeIndex = std::type_index(typeid(T));
	return res;
}

#endif // SIGNATURE_TYPE_HPP
