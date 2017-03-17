#ifndef NODE_EVALUATOR_HPP
#define NODE_EVALUATOR_HPP

#include <boost/variant.hpp>
#include "EvaluationNode.hpp"

class NodeEvaluator : public boost::static_visitor<Data>
{
	public:
		Data operator()(const Identifier& identifier);
		Data operator()(const Data& data);
		Data operator()(const FunctionCall& functionCall);
};

#endif // NODE_EVALUATOR_HPP
