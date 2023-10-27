#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Node
{
public:
	Node();
	Node(int a);
	void load();
	void print();
	void printChildren(std::vector<Node*> const& childrens, int j);
	void save();
	void saveChildrens(std::vector<Node*> const& childrens, std::ofstream& fout);
	Node* parent;
	Node* current;
	std::string name;
private:
	int value;
	std::vector<Node*> childrens;
};