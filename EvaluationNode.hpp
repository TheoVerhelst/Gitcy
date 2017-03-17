#ifndef EVALUATION_NODE_HPP
#define EVALUATION_NODE_HPP

#include <string>
#include <boost/blank.hpp>
#include <boost/variant.hpp>
#include "Data.hpp"

typedef std::string Identifier;
typedef boost::blank FunctionCall;
typedef boost::variant<Identifier, Data, FunctionCall> EvaluationNode;

#endif // EVALUATION_NODE_HPP
