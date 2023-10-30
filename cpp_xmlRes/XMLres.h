#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include "Node.h"

class XMLresource : std::enable_shared_from_this<XMLresource>
{
public:
	XMLresource();
	XMLresource(int a, std::string tag);
	void load();
	void print();
	void save();
	std::weak_ptr<XMLresource> getPtr();
private:
	void saveChildrens(/*std::shared_ptr<*/std::vector<std::shared_ptr<Node>>/*> */const& childrens, std::ofstream& fout);
	void printChildrens(std::vector<std::shared_ptr<Node>> const& childrens, int j);
	std::shared_ptr<Node> node_ptr;
};