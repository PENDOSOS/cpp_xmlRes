// cpp_xmlRes.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include "XMLres.h"

using namespace std;

int main()
{
	XMLresource tree;

	tree.load();

	tree.print();

	tree.save();

	auto a = tree.begin();

	a;

	++a;
	++a;
	++a;
	++a;
	++a;

	a = tree.end();

	return 0;
}