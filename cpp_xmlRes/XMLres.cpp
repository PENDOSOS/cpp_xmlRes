#include "XMLres.h"

std::unique_ptr<XMLresource> XMLresource::create()
{
	std::unique_ptr<XMLresource> new_xml(new XMLresource);
	return std::move(new_xml);
}

void XMLresource::load(std::string const& file_name)
{
	std::string line;
	std::ifstream fin(file_name);
	while (std::getline(fin, line))
	{
		if (line[0] == '<' && line[1] != '/')
		{
			if (node_ptr == nullptr)
			{
				node_ptr = std::make_shared<Node>();
				node_ptr->tag = line.substr(1, line.size() - 2);
				std::getline(fin, line);
				node_ptr->value = std::stoi(line.substr(6));
			}
			else
			{
				std::string temp_tag = line.substr(1, line.size() - 2);
				std::getline(fin, line);
				std::shared_ptr<Node> temp = std::make_shared<Node>(std::stoi(line.substr(6)), temp_tag);
				node_ptr->children.push_back(std::move(temp));
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
	//if (node_ptr != nullptr)
	{
		std::cout << node_ptr->value << std::endl;
		printChildrens(node_ptr->children, 3);
	}
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

void XMLresource::save(std::string const& file_name)
{
	std::ofstream fout(file_name);
	fout << "<" << node_ptr->tag << ">" << std::endl;
	fout << "value=" << node_ptr->value << std::endl;
	saveChildrens(node_ptr->children, fout);
	fout << "</" << node_ptr->tag << ">" << std::endl;
	fout.close();
}

void XMLresource::saveChildrens(std::vector<std::shared_ptr<Node>> const& childrens, std::ofstream& fout)
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

XMLresource::iterator XMLresource::add(std::string const& name, int value, iterator const& node)
{
	if (node == end())
		return node;
	auto iterator = begin();
	while (iterator != end())
	{
		if (iterator == node)
		{
			std::shared_ptr<Node> new_node = std::make_shared<Node>(value, name);
			node.p->children.push_back(std::move(new_node));
			node.p->children.back()->parent = node.p->getPtr();
		}
		++iterator;
	}
	XMLresource::iterator added_elem(&*node.p->children.back());
	return added_elem;
}

XMLresource::iterator XMLresource::find(std::string const& name) const&
{
	auto iterator = begin();
	while (iterator != end())
	{
		if (iterator.p->tag == name)
		{
			return iterator;
		}
		++iterator;
	}
	return end();
}

XMLresource::iterator XMLresource::find(int value) const&
{
	auto iterator = begin();
	if (iterator != nullptr)
	{
		while (iterator != end())
		{
			if (iterator.p->value == value)
			{
				return iterator;
			}
			++iterator;
		}
		return end();
	}
	else
		return iterator;
}

bool XMLresource::erase(iterator const& node) const&
{
	if (node.p->parent == nullptr)
		return false;
	else
	{
		if (node.p->children.size() != 0)
		{
			for (int i = 0; i < node.p->children.size(); i++)
				node.p->parent->children.push_back(std::move(node.p->children[i]));
		}
		auto parent = node.p->parent;
		auto iterator = parent->children.begin();
		while (iterator->get() != node.p)
			++iterator;
		parent->children.erase(iterator);
		return true;
	}
}

XMLresource::iterator XMLresource::begin() const&
{
	return iterator(node_ptr.get());
}

XMLresource::iterator XMLresource::end() const&
{
	auto xml_end = &node_ptr->children.end();
	return XMLresource::iterator (xml_end->_Ptr->get());
}