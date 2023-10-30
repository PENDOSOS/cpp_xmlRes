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

	return 0;
}