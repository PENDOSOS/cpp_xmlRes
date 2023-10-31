// cpp_xmlRes.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include "XMLres.h"
#include <algorithm>

using namespace std;

int main()
{
	auto tree = XMLresource::create();

	tree->load();

	tree->print();

	//auto a = tree->add("goyda", 7, tree->end());

	//tree->print();
	//tree->save();

	auto c = tree->end();
	auto b = tree->begin();
	++b;
	++b;
	++b;
	++b;
	++b;

	return 0;
}