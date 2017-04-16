#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <map>
#include <string>
#include <memory>
#include <boost/blank.hpp>
#include <boost/variant.hpp>
#include <Tree.hpp>

// Forward declarations
class Scope;
class Value;
typedef Tree<boost::variant<std::string, Value, boost::blank>> EvaluationTree;

class Callable
{
	public:
		// Destructor.
		virtual ~Callable() = default;

		virtual Value call(const EvaluationTree& expression, Scope& scope) = 0;
};

#endif // CALLABLE_HPP
