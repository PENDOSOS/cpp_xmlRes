#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>

class XMLresource : std::enable_shared_from_this<XMLresource>
{
public:
	XMLresource();
	XMLresource(int a, std::string tag);
	void load();
	void print();
	void printChildren(std::vector<std::shared_ptr<XMLresource>> const& childrens, int j);
	void save();
	void saveChildrens(std::vector<std::shared_ptr<XMLresource>> const& childrens, std::ofstream& fout);
	std::shared_ptr<XMLresource> parent;
	std::shared_ptr<XMLresource> current;
	std::string name;
private:
	int value;
	std::vector<std::shared_ptr<XMLresource>> children;
	std::string tag;
};