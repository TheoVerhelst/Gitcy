#ifndef EVALUATION_TREE_HPP
#define EVALUATION_TREE_HPP

#include <vector>
#include <EvaluationNode.hpp>

/// An evaluation tree is a convenient in-memory representation of the code.
/// It consists of leaves for values and identifiers, and branches for function
/// calls.
class EvaluationTree
{
	public:
		/// Typedef for tree iteration.
		typedef typename std::vector<EvaluationTree>::iterator Iterator;

		/// Typedef for tree non-modifying iteration.
		typedef typename std::vector<EvaluationTree>::const_iterator ConstIterator;

		/// Constructor for an empty tree.
		EvaluationTree() = default;

		/// Constructor.
		/// \param node The value of the node (function call, value, ...).
		/// \param children The children trees of the node, if the node is a
		/// function call.
		EvaluationTree(const EvaluationNode& node, const std::vector<EvaluationTree>& children=std::vector<EvaluationTree>());

		/// Get the value of the evaluation node.
		const EvaluationNode& getNode() const;

		/// Returns the number of children trees.
		/// \returns The number of children trees.
		size_t numberChildren() const;

		/// Checks whether this tree has children trees.
		/// \returns numberChildren() > 0.
		bool hasChildren() const;

		/// Returns the index-th child.
		/// \param index The index of the child to get.
		/// \returns The requested child.
		/// \throws std::out_of_bounds if index >= numberChildren().
		const EvaluationTree& getChild(std::size_t index) const;

		/// Gets an iterator pointing to the first children.
		/// \returns An iterator, possibly end() if not hasChildren().
		Iterator begin();

		/// Gets an const iterator pointing to the first children.
		/// \returns An iterator, possibly end() if not hasChildren().
		ConstIterator begin() const;

		/// Gets the past-the-end iterator.
		/// \returns The past-the-end iterator.
		Iterator end();

		/// Gets the past-the-end const iterator.
		/// \returns The past-the-end const iterator.
		ConstIterator end() const;

	private:
		EvaluationNode _node; ///< The current node.
		std::vector<EvaluationTree> _children; /// The children trees.
};

#endif // EVALUATION_TREE_HPP
