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
			if (node_ptr == nullptr)
			{
				node_ptr = std::make_shared<Node>();
				node_ptr->tag = line;
				std::getline(fin, line);
				node_ptr->value = std::stoi(std::string(1, line[line.size() - 1]));
			}
			else
			{
				std::string temp_tag = line;
				std::getline(fin, line);
				std::shared_ptr<Node> temp = std::make_shared<Node>(std::stoi(std::string(1, line[line.size() - 1])), temp_tag);
				node_ptr->children->push_back(temp);
				node_ptr->children->back()->parent = node_ptr->getPtr();
				node_ptr = node_ptr->children->back();
			}
		}
		else if (line[0] == '<' && line[1] == '/' && node_ptr->parent != nullptr)
		{
			node_ptr = node_ptr->parent;
		}
	}
	fin.close();
}

/*void XMLresource::print()
{
	std::cout << this->value << std::endl;
	printChildren(this->children, 3);
}*/

/*void XMLresource::printChildren(std::vector<std::shared_ptr<XMLresource>> const& childrens, int j)
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
}*/

/*void XMLresource::save()
{
	std::ofstream fout("xml1.txt");
	fout << "value=" << this->value;
	saveChildrens(this->children, fout);
	fout.close();
}*/

/*void XMLresource::saveChildrens(std::vector<std::shared_ptr<XMLresource>> const& childrens, std::ofstream& fout)
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
}*/

std::weak_ptr<XMLresource> XMLresource::getPtr() 
{
	return shared_from_this();
}