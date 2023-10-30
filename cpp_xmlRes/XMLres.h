#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include "Node.h"
#include "Iterator.h"

class XMLresource : public std::enable_shared_from_this<XMLresource>
{
public:
	typedef Iterator<Node> iterator;
	XMLresource();
	XMLresource(int a, std::string tag);
	void load();
	void print();
	void save();
	std::shared_ptr<XMLresource> getPtr();

	iterator begin() const;
	iterator end() const;
private:
	void saveChildrens(/*std::shared_ptr<*/std::vector<std::shared_ptr<Node>>/*> */const& childrens, std::ofstream& fout);
	void printChildrens(std::vector<std::shared_ptr<Node>> const& childrens, int j);
	std::shared_ptr<Node> node_ptr;
	//const size_t size;
};