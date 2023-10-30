#pragma once

#include <iostream>
#include <iterator>

template <typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	
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
		auto new_p = p->children[0];
		auto a = &*new_p;
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
		auto temp = p;
		p = &*p->parent;
		auto iter = p->children.begin();
		while (&**iter != temp)
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
		this->p = p;
		return *this;
	}
}