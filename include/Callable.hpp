#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include <ostream>
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

/// Overload of the output operator for a Callable value. Since we have no
/// information from the object, it just outputs the type name "Callable".
/// \param os The stream to output to.
/// \param callable The object to output.
/// \returns os.
std::ostream& operator<<(std::ostream& os, const Callable& callable);

#endif // CALLABLE_HPP
