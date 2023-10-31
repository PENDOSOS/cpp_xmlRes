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

	tree->save();

	return 0;
}