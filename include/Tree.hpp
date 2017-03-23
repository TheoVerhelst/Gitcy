#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <vector>
#include <memory>

template <typename T>
class Tree
{
	public:
		typedef std::shared_ptr<Tree<T>> Ptr;
		static Ptr create(const T& value,
				const std::vector<Ptr>& children=std::vector<Ptr>());
		const T& getValue() const;
		T& getValue();
		void setValue(const T& newValue);
		size_t numberChildren() const;
		bool hasChildren() const;
		void addChild(Ptr child);
		void setChild(size_t n, Ptr newChild);
		void removeChild(size_t n);
		const Ptr getChild(size_t n) const;
		Ptr getChild(size_t n);
		void resolveChildren(Ptr self);
		const Ptr getParent() const;

	private:
		Tree(const T& value,
				const std::vector<Ptr>& children=std::vector<Ptr>());
		void setParent(Ptr newParent);

		std::vector<Ptr> _children;
		Ptr _parent;
		Ptr _self;
		T _data;
};

template <typename T>
typename Tree<T>::Ptr Tree<T>::create(const T& value,
		const std::vector<Tree<T>::Ptr>& children)
{
	Ptr res{new Tree<T>(value, children)};
	res->_self = res;
	return res;
}

template <typename T>
Tree<T>::Tree(const T& value,
		const std::vector<Tree<T>::Ptr>& children):
	_children(children),
	_data(value)
{
}

template <typename T>
const T& Tree<T>::getValue() const
{
	return _data;
}

template <typename T>
T& Tree<T>::getValue()
{
	return _data;
}

template <typename T>
void Tree<T>::setValue(const T& newValue)
{
	_data = newValue;
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
void Tree<T>::addChild(Tree<T>::Ptr child)
{
	_children.push_back(child);
	child->setParent(_self);
}

template <typename T>
void Tree<T>::setChild(size_t n, Tree<T>::Ptr newChild)
{
	_children[n]->setParent(nullptr);
	newChild->setParent(_self);
	_children[n] = newChild;
}

template <typename T>
void Tree<T>::removeChild(size_t n)
{
	_children[n]->setParent(nullptr);
	_children.erase(_children.begin() + n);
}

template <typename T>
const typename Tree<T>::Ptr Tree<T>::getChild(size_t n) const
{
	return _children[n];
}

template <typename T>
typename Tree<T>::Ptr Tree<T>::getChild(size_t n)
{
	return _children[n];
}

template <typename T>
void Tree<T>::setParent(Tree<T>::Ptr newParent)
{
	_parent = newParent;
}

template <typename T>
const typename Tree<T>::Ptr Tree<T>::getParent() const
{
	return _parent;
}

#endif
