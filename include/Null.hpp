#ifndef NULL_HPP
#define NULL_HPP

#include <ostream>

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

#endif // NULL_HPP
