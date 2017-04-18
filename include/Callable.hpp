#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <functional>

// Forward declarations
class Scope;
class Value;
class EvaluationTree;

/// A Callable is any C++ object or function that can be called with the
/// following signature. A Callable takes an evaluation tree, and the enclosing
/// scope, and returns a value. It can do whatever it wants with the evaluation
/// tree.
typedef std::function<Value(const EvaluationTree& expression, Scope& scope)> Callable;

#endif // CALLABLE_HPP
