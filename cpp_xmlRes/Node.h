#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Node : public std::enable_shared_from_this<Node>
{
public:
	Node();
	Node(int _value, std::string _tag);
	std::shared_ptr<Node> getPtr();
	std::shared_ptr<Node> parent;
	std::shared_ptr<std::vector<std::shared_ptr<Node>>> children;
	int value;
	std::string tag;
};