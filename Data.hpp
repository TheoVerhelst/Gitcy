#ifndef DATA_HPP
#define DATA_HPP

#include <ostream>
#include <boost/variant.hpp>

class Function;

class Null
{
};

std::ostream& operator<<(std::ostream& os, const Null& null);

typedef boost::variant<Null, bool, int, float, std::string, boost::recursive_wrapper<Function>> Data;

#endif // DATA_HPP
