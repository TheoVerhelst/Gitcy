#ifndef EVALUATION_NODE_HPP
#define EVALUATION_NODE_HPP

#include <string>
#include <boost/blank.hpp>
#include <boost/variant.hpp>
#include <Tree.hpp>
#include <Value.hpp>

/// Represents an identifier in the evaluation tree of the interpreter. In
/// facts, we only need to store the name of the identifier.
typedef std::string Identifier;

/// In the evaluation tree, a call is only defined by its argument, the first
/// one being the callable to call and the remaining ones the arguments.
/// So we have no data to store in the node itself (only in its childs).
typedef boost::blank Call;

/// Represents a node in the evaluation tree. A node may be an identifier to
/// evaluate at runtime, a literal representing a value or a call.
/// This type allows to store them seamlessly.
typedef boost::variant<Identifier, Value, Call> EvaluationNode;

typedef Tree<EvaluationNode> EvaluationTree;

#endif // EVALUATION_NODE_HPP
