#include "Node.h"

Node::Node()
{
	//children = std::make_shared<std::vector<std::shared_ptr<Node>>>();
	//parent = nullptr;
	value = 0;
}

Node::Node(int _value, std::string _tag)
{
	this->value = _value;
	this->tag = _tag;
	//children = std::make_shared<std::vector<std::shared_ptr<Node>>>();
}

std::shared_ptr<Node> Node::getPtr()
{
	return shared_from_this();
}