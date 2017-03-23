#ifndef OVERLOAD_HPP
#define OVERLOAD_HPP

#include <functional>
#include <ostream>
#include <vector>
#include <Data.hpp>
#include <SignatureType.hpp>

/// Conveniency typedef for a functor.
typedef std::function<Data(const std::vector<Data>&)> Functor;

/// An overload is an implementation of a script function. While a script
/// function is just a list of overloads bound to a name, an overload contains
/// the specification of its parameters and a pointer to the C++ function to
/// call.
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
		/// Constructor.
		/// \param typeList The list of parameters this overload can accept.
		/// \param isVariadic Indicates whether this overload is variadic.
		/// \param functor A pointer to the C++ function to call.
		Overload(const std::vector<SignatureType>& typeList, bool isVariadic, const Functor& functor);

		/// Checks whether the argument list is valid for calling this overload.
		/// \param arguments The argument list.
		/// \returns True is the ardument list matches this overload, false
		/// otherwise.
		bool matches(const std::vector<Data>& arguments) const;

		/// Call the C++ function with the given arguments.
		/// \pre matches(arguments)
		/// \param arguments The arguments to forward to the function.
		/// \return The return value of the function.
		Data operator()(const std::vector<Data>& arguments) const;

		/// Overload of the output operator. It just shows the list of types
		/// that are accepted in this overload, with an ellipsis if it is
		/// variadic.
		/// \param os The stream to output to.
		/// \param signature The overload to output.
		/// \returns os.
		/// \TODO rename signature to overload.
		friend std::ostream& operator<<(std::ostream& os, const Overload& signature);

	private:
		/// The list of types accepted by this overload.
		std::vector<SignatureType> _typeList;

		/// Indicates whether this overload is variadic.
		bool _isVariadic;

		/// The function pointer to the C++ function to call.
		Functor _functor;
};


#endif // OVERLOAD_HPP
