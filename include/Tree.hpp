#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <vector>
#include <memory>

template <typename T>
class Tree
{
	public:
		typedef typename std::vector<Tree>::iterator Iterator;
		typedef typename std::vector<Tree>::const_iterator ConstIterator;

		Tree() = default;
		Tree(const T& value, const std::vector<Tree>& children=std::vector<Tree>());
		const T& getValue() const;
		size_t numberChildren() const;
		bool hasChildren() const;
		const Tree& getChild(std::size_t index) const;
		Iterator begin();
		ConstIterator begin() const;
		Iterator end();
		ConstIterator end() const;

	private:
		std::vector<Tree> _children;
		T _data;
};

template <typename T>
Tree<T>::Tree(const T& value, const std::vector<Tree<T>>& children):
	_children{children},
	_data{value}
{
}

template <typename T>
const T& Tree<T>::getValue() const
{
	return _data;
}

template <typename T>
size_t Tree<T>::numberChildren() const
{
	return _children.size();
}

template <typename T>
bool Tree<T>::hasChildren() const
{
	return not _children.empty();
}

template <typename T>
const Tree<T>& Tree<T>::getChild(std::size_t index) const
{
	return _children.at(index);
}

template <typename T>
typename Tree<T>::Iterator Tree<T>::begin()
{
	return _children.begin();
}

template <typename T>
typename Tree<T>::ConstIterator Tree<T>::begin() const
{
	return _children.begin();
}

template <typename T>
typename Tree<T>::Iterator Tree<T>::end()
{
	return _children.end();
}

template <typename T>
typename Tree<T>::ConstIterator Tree<T>::end() const
{
	return _children.end();
}

#endif
