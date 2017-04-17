#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <functional>
#include <boost/variant.hpp>
#include <boost/blank.hpp>
#include <Tree.hpp>

// Forward declarations
class Scope;
class Value;
typedef Tree<boost::variant<std::string, Value, boost::blank>> EvaluationTree;

typedef std::function<Value(const EvaluationTree& expression, Scope& scope)> Callable;

#endif // CALLABLE_HPP
