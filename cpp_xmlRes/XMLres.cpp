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
				node_ptr->children.push_back(temp);
				node_ptr->children.back()->parent = node_ptr->getPtr();
				node_ptr = node_ptr->children.back()->getPtr();
			}
		}
		else if (line[0] == '<' && line[1] == '/' && node_ptr->parent != nullptr)
		{
			node_ptr = node_ptr->parent;
		}
	}
	fin.close();
}

void XMLresource::print()
{
	std::cout << node_ptr->value << std::endl;
	printChildrens(node_ptr->children, 3);
}

void XMLresource::printChildrens(std::vector<std::shared_ptr<Node>> const& childrens, int j)
{
	int i = 0;
	while (i < childrens.size())
	{
		std::cout << std::setw(j) << childrens[i]->value << std::endl;
		if (childrens.size() != 0)
		{
			printChildrens(childrens[i]->children, j + 3);
		}
		i++;
	}
}

void XMLresource::save()
{
	std::ofstream fout("xml_saved.txt");
	fout << "<" << node_ptr->tag << ">" << std::endl;
	fout << "value=" << node_ptr->value << std::endl;
	saveChildrens(node_ptr->children, fout);
	fout << "</" << node_ptr->tag << ">" << std::endl;
	fout.close();
}

void XMLresource::saveChildrens(/*std::shared_ptr<*/std::vector<std::shared_ptr<Node>>/*> */const& childrens, std::ofstream& fout)
{
	int i = 0;
	while (i < childrens.size())
	{
		fout << "<" << childrens[i]->tag << ">" << std::endl;
		fout << "value=" << childrens[i]->value << std::endl;
		if (childrens.size() != 0)
		{
			saveChildrens(childrens[i]->children, fout);
		}
		fout << "</" << childrens[i]->tag << ">" << std::endl;
		i++;
	}
}

std::shared_ptr<XMLresource> XMLresource::getPtr() 
{
	return shared_from_this();
}

XMLresource::iterator XMLresource::begin() const
{
	return iterator(node_ptr.get());
}

XMLresource::iterator XMLresource::end() const
{
	return iterator(nullptr);
}