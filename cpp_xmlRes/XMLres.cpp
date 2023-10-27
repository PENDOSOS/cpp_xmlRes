#include "XMLres.h"

XMLresource::XMLresource()
{
}

XMLresource::XMLresource(int a, std::string tag)
{
}

void XMLresource::load()
{
	std::string line;
	std::ifstream fin("xml.txt");
	while (std::getline(fin, line))
	{
		if (line[0] == '<' && line[1] != '/')
		{
			if (current == nullptr)
			{
				current = std::make_shared<XMLresource>();
				current->tag = line;
				std::getline(fin, line);
				current->value = std::stoi(std::string(1, line[line.size() - 1]));
			}
			else
			{
				std::string temp_tag = line;
				std::getline(fin, line);
				std::shared_ptr<XMLresource> temp = std::make_shared<XMLresource>(std::stoi(std::string(1, line[line.size() - 1])), temp_tag);
				current->children.push_back(temp);
				current->children.back()->parent = current;
				current = current->children.back();
			}
		}
		else if (line[0] == '<' && line[1] == '/')
		{
			current = current->parent.lock();
		}
	}
	fin.close();
}

void XMLresource::print()
{
	std::cout << this->value << std::endl;
	printChildren(this->children, 3);
}

void XMLresource::printChildren(std::vector<std::shared_ptr<XMLresource>> const& childrens, int j)
{
	int i = 0;
	while (i < childrens.size())
	{
		std::cout << std::setw(j) << childrens[i]->value << std::endl;
		if (childrens.size() != 0)
		{
			printChildren(childrens[i]->children, j + 3);
		}
		i++;
	}
}

void XMLresource::save()
{
	std::ofstream fout("xml1.txt");
	fout << "value=" << this->value;
	saveChildrens(this->children, fout);
	fout.close();
}

void XMLresource::saveChildrens(std::vector<std::shared_ptr<XMLresource>> const& childrens, std::ofstream& fout)
{
	int i = 0;
	while (i < childrens.size())
	{
		fout << childrens[i]->value << std::endl;
		if (childrens.size() != 0)
		{
			saveChildrens(childrens[i]->children, fout);
		}
		i++;
	}
}

std::weak_ptr<XMLresource> XMLresource::getPtr() 
{
	return shared_from_this();
}