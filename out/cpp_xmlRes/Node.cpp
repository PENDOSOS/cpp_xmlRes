#include "Node.h"

Node::Node()
{
	current = nullptr;
	parent = current;
	value = 0;
}

Node::Node(int _value, std::string _tag)
{
	this->value = _value;
	this->tag = _tag;
}

std::weak_ptr<Node> Node::getPtr()
{
	return weak_from_this();
}