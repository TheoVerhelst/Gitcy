#ifndef EVALUATION_TREE_HPP
#define EVALUATION_TREE_HPP

#include <vector>
#include <EvaluationNode.hpp>

class EvaluationTree
{
	public:
		typedef typename std::vector<EvaluationTree>::iterator Iterator;
		typedef typename std::vector<EvaluationTree>::const_iterator ConstIterator;

		EvaluationTree() = default;
		EvaluationTree(const EvaluationNode& node, const std::vector<EvaluationTree>& children=std::vector<EvaluationTree>());
		const EvaluationNode& getNode() const;
		size_t numberChildren() const;
		bool hasChildren() const;
		const EvaluationTree& getChild(std::size_t index) const;
		Iterator begin();
		ConstIterator begin() const;
		Iterator end();
		ConstIterator end() const;

	private:
		EvaluationNode _node;
		std::vector<EvaluationTree> _children;
};

#endif // EVALUATION_TREE_HPP
