#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <map>
#include <string>
#include <memory>
#include <Tree.hpp>
#include <Scope.hpp>

// Forward declarations
class Value;
typedef std::string Identifier;
typedef boost::blank Call;
typedef boost::variant<Identifier, Value, Call> EvaluationNode;

class Callable
{
	public:
		// Destructor.
		virtual ~Callable() = default;

		virtual Value call(const Tree<EvaluationNode>::Ptr& expression, Scope& scope) = 0;
};

#endif // CALLABLE_HPP
