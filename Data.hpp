#ifndef DATA_HPP
#define DATA_HPP

#include <ostream>
#include <boost/variant.hpp>

// Forward declaration
class Function;

/// Represents the null type in scripts, and has only one value. It is used as
/// a return value for function returning nothing, for example.
class Null
{
};

/// Overload of the output operator for the Null type. It always output "null".
/// \param os The stream to output to.
/// \param null The null value to output.
/// \returns os.
std::ostream& operator<<(std::ostream& os, const Null& null);

/// The type used in C++ to represent any value in script. It is more safe than
/// a pointer to void, as boost::variant enfore type and has compile-time and
/// runtime checks.
/// \TODO change float to double
typedef boost::variant<Null, bool, int, float, std::string, boost::recursive_wrapper<Function>> Data;

#endif // DATA_HPP
