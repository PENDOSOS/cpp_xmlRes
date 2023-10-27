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
	//void print();
	//void printChildren(std::vector<std::shared_ptr<XMLresource>> const& childrens, int j);
	//void save();
	//void saveChildrens(std::vector<std::shared_ptr<XMLresource>> const& childrens, std::ofstream& fout);
	std::weak_ptr<XMLresource> getPtr();
private:
	std::shared_ptr<Node> node_ptr;
};