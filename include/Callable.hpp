#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <functional>

// Forward declarations
class Scope;
class Value;
class EvaluationTree;

typedef std::function<Value(const EvaluationTree& expression, Scope& scope)> Callable;

#endif // CALLABLE_HPP
