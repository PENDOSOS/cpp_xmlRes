#pragma once

#include <iostream>
#include <iterator>

template <typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	~Iterator() = default;
	Iterator(Iterator const& it);
	
	bool operator==(Iterator const& other) const;
	bool operator!=(Iterator const& other) const;
	typename Iterator::reference operator*() const;
	Iterator& operator++();
private:
	Iterator(ValueType* p);

	Iterator<ValueType>& levelUp(ValueType* p);
	ValueType* p;
	friend class XMLresource;
};

template <typename ValueType>
Iterator<ValueType>::Iterator(ValueType* p) : p(p) {}

template <typename ValueType>
Iterator<ValueType>::Iterator(Iterator const& it) : p(it.p) {}

template<typename ValueType>
bool Iterator<ValueType>::operator!=(Iterator const& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool Iterator<ValueType>::operator==(Iterator const& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename Iterator<ValueType>::reference Iterator<ValueType>::operator*() const
{
	return *p;
}

template<typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator++()
{
	if (p->children.size() != 0)
	{
		auto new_p = p->children[0];	//new_p - shared_ptr<Node>
		auto a = &*new_p;				//a - Node*
		p = a;
		return *this;
	}
	else
	{
		return levelUp(p);
	}
}

template<typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::levelUp(ValueType* p)
{
	if (p->parent != nullptr)
	{
		auto temp = p;						//temp - Node*
		p = &*p->parent;					//p->parent - shared_ptr<Node>, &*p->parent - Node*
		auto iter = p->children.begin();	//p->children.begin() - vector<shared_ptr<Node>> iterator
		while (&**iter != temp)				//&**iter - Node*
		{
			++iter;
		}
		++iter;
		if (iter != p->children.end())
		{
			this->p = &**iter;
			return *this;
		}
		else
			return levelUp(p);
	}
	else
	{
		auto xml_end = &p->children.end();
		auto end_of_children = xml_end->_Ptr->get();
		this->p = end_of_children;
		return *this;
	}
}