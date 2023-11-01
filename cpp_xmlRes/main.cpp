// cpp_xmlRes.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include "XMLres.h"
#include <algorithm>

using namespace std;

int main()
{
	auto tree = XMLresource::create();

	tree->load("xml.txt");

	tree->print();

	auto a = tree->add("goyda", 7, tree->begin());

	auto c = tree->find(7);
	auto b = tree->find("goyda");

	tree->erase(b);
	tree->save("xml_saved.txt");

	return 0;
}