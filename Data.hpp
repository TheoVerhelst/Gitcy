#ifndef DATA_HPP
#define DATA_HPP

#include <boost/variant.hpp>

class Function;

typedef boost::variant<bool, int, float, std::string, boost::recursive_wrapper<Function>> Data;

#endif // DATA_HPP
