#include "stdafx.h"
#include "RBF.h"

#include <iostream>
#include <vector>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	cout << "----" << endl;
	for (int i : v)
	{
		cout << i << endl;
	}

	cout << "----" << endl;
	for (int i : rbf::Reverse(v))
	{
		cout << i << endl;
	}

	getchar();
	return 0;
}
