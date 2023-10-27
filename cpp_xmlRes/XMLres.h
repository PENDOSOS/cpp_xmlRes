#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class XMLresource
{
public:
	XMLresource();
	XMLresource(int a);
	void load();
	void print();
	void printChildren(std::vector<XMLresource*> const& childrens, int j);
	void save();
	void saveChildrens(std::vector<XMLresource*> const& childrens, std::ofstream& fout);
	XMLresource* parent;
	XMLresource* current;
	std::string name;
private:
	int value;
	std::vector<XMLresource*> children;
	std::string tag;
};