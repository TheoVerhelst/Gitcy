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

		std::vector<Ptr> m_children;
		Ptr m_parent;
		Ptr m_self;
		T m_data;
};

#include "Tree.impl"

#endif
