#ifndef OVERLOAD_HPP
#define OVERLOAD_HPP

#include <ostream>
#include <vector>
#include <SignatureType.hpp>

// Forward declarations
class Value;

/// An overload is an implementation of a script function. While a script
/// function is just a list of overloads bound to a name, an overload contains
/// the specification of its parameters and a C++ function to call (the
/// operator() to override).
///
/// An overload accepts a list of parameter types being instances of
/// SignatureType. This includes the default-constructed instance, meaning that
/// any type is valid for this parameter.
///
/// An overload may be variadic. If so, then the function can accept a number
/// of arguments greater or equal to the number of parameter types in the list.
/// The type of the extra arguments must match the type of the last parameter in
/// the list.
class Overload
{
	public:
		/// Destructor.
		virtual ~Overload() = default;

		/// Checks whether the argument list is valid for calling this overload.
		/// \param arguments The argument list.
		/// \returns True is the ardument list matches this overload, false
		/// otherwise.
		bool matches(const std::vector<Value>& arguments) const;

		/// Call the function with the given arguments.
		/// \pre matches(arguments)
		/// \param arguments The arguments to forward to the function.
		/// \return The return value of the function.
		virtual Value call(const std::vector<Value>& arguments) const = 0;

		/// Overload of the output operator. It just shows the list of types
		/// that are accepted in this overload, with an ellipsis if it is
		/// variadic.
		/// \param os The stream to output to.
		/// \param signature The overload to output.
		/// \returns os.
		friend std::ostream& operator<<(std::ostream& os, const Overload& overload);

		/// Returns whether this overload is variadic.
		/// \returns True if this overload is variadic, false otherwise.
		bool isVariadic() const;

	protected:
		/// Constructor.
		/// \param typeList The list of parameters this overload can accept.
		/// \param isVariadic Indicates whether this overload is variadic.
		Overload(const std::vector<SignatureType>& typeList, bool isVariadic);

	private:
		/// The list of types accepted by this overload.
		std::vector<SignatureType> _typeList;

		/// Indicates whether this overload is variadic.
		bool _isVariadic;
};


#endif // OVERLOAD_HPP
