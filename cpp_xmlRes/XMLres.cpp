#include "XMLres.h"

XMLresource::XMLresource()
{
	current = nullptr;
	parent = nullptr;
	value = 0;
}

XMLresource::XMLresource(int a)
{
	this->value = a;
}

void XMLresource::load()
{
	std::string line;
	this->name = line;
	std::ifstream fin("xml.txt");
	while (std::getline(fin, line))
	{
		if (line[0] == '<' && line[1] != '/')
		{
			if (current == nullptr)
			{
				current = this;
				std::getline(fin, line);
				current->value = std::stoi(std::string(1, line[line.size() - 1]));
			}
			else
			{
				std::getline(fin, line);
				XMLresource* temp = new XMLresource(std::stoi(std::string(1, line[line.size() - 1])));
				current->childrens.push_back(temp);
				temp->parent = current;
				current = temp;
				current->name = line;
			}
		}
		else if (line[0] == '<' && line[1] == '/')
		{
			current = current->parent;
		}
	}
	fin.close();
}

void XMLresource::print()
{
	std::cout << this->value << std::endl;
	printChildren(this->childrens, 3);
}

void XMLresource::printChildren(std::vector<XMLresource*> const& childrens, int j)
{
	int i = 0;
	while (i < childrens.size())
	{
		std::cout << std::setw(j) << childrens[i]->value << std::endl;
		if (childrens.size() != 0)
		{
			printChildren(childrens[i]->childrens, j + 3);
		}
		i++;
	}
}

void XMLresource::save()
{
	std::ofstream fout("xml1.txt");
	fout << this->name;
	fout << "value=" << this->value;
	saveChildrens(this->childrens, fout);
	fout << "value=" << this->name;
	fout.close();
}

void XMLresource::saveChildrens(std::vector<XMLresource*> const& childrens, std::ofstream& fout)
{
	int i = 0;
	while (i < childrens.size())
	{
		fout << childrens[i]->name << std::endl;
		fout << childrens[i]->value << std::endl;
		if (childrens.size() != 0)
		{
			saveChildrens(childrens[i]->childrens, fout);
		}
		i++;
	}
}