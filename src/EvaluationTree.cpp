#include <Utils.hpp>
#include <EvaluationTree.hpp>

EvaluationTree::EvaluationTree(const EvaluationNode& node, const std::vector<EvaluationTree>& children):
	_node{node},
	_children{children}
{
	assert(children.empty() or node.type() == typeid(Call));
}

const EvaluationNode& EvaluationTree::getNode() const
{
	return _node;
}

size_t EvaluationTree::numberChildren() const
{
	return _children.size();
}

bool EvaluationTree::hasChildren() const
{
	return not _children.empty();
}

const EvaluationTree& EvaluationTree::getChild(std::size_t index) const
{
	assert(index < _children.size());
	return _children.at(index);
}

typename EvaluationTree::Iterator EvaluationTree::begin()
{
	return _children.begin();
}

typename EvaluationTree::ConstIterator EvaluationTree::begin() const
{
	return _children.begin();
}

typename EvaluationTree::Iterator EvaluationTree::end()
{
	return _children.end();
}

typename EvaluationTree::ConstIterator EvaluationTree::end() const
{
	return _children.end();
}

std::ostream& operator<<(std::ostream& os, const EvaluationTree& object)
{
	os << "(" << object.getNode() << Utils::join(" ", object._children.begin(), object._children.end()) << ")";
	return os;
}
