#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include <iostream>
#include <vector>
using namespace std;



template<typename VisitorFunc>
void visitFiles(const char* filter, VisitorFunc visitor)
{
	struct _finddata_t c_file;

	intptr_t hFile = _findfirst(filter, &c_file);
	if (hFile == -1L)
		return;

	do
	{
		visitor(c_file.name);
	}
	while (_findnext(hFile, &c_file) == 0);

	_findclose(hFile);
}

void getFiles(const char* filter, std::vector<std::string>& files)
{
	files.clear();
	struct _finddata_t c_file;

	intptr_t hFile = _findfirst(filter, &c_file);
	if (hFile == -1L)
		return;

	do
	{
		files.push_back(c_file.name);
	}
	while (_findnext(hFile, &c_file) == 0);

	_findclose(hFile);
}
