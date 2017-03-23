#ifndef SIGNATURE_TYPE_HPP
#define SIGNATURE_TYPE_HPP

#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <experimental/optional>
#include "Data.hpp"

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
		/// Default constructor. The resulting object matches any argument.
		SignatureType();

		/// Constructor. The resulting object matches only the given type.
		/// \param type The type to match.
		SignatureType(const std::type_info& type);

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
		/// The type to match, if any. We use the optional class in the case we
		/// match any type.
		std::experimental::optional<std::type_index> _typeIndex;

		/// Map of pretty names for types to display in the output operator.
		static const std::map<std::type_index, std::string> _typePrettyNames;
};

#endif // SIGNATURE_TYPE_HPP
