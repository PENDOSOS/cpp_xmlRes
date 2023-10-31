#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include "Node.h"
#include "Iterator.h"

class XMLresource 
{
public:
	typedef Iterator<Node> iterator;

	static std::unique_ptr<XMLresource> create();
	void load();
	void print();
	void save();
	iterator add(std::string const& name, int value, iterator const& node);
	iterator find(std::string const& name) const&;
	iterator find(int value) const&;
	bool erase(iterator const& node) const&;

	iterator begin() const&;
	iterator end() const&;
private:
	XMLresource() = default;
	void saveChildrens(std::vector<std::shared_ptr<Node>> const& childrens, std::ofstream& fout);
	void printChildrens(std::vector<std::shared_ptr<Node>> const& childrens, int j);
	std::shared_ptr<Node> node_ptr;
};