#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool check_files(ifstream& file1, ifstream& file2)
{
	char buf1, buf2;
	while ((!file1.eof()) || (!file2.eof()))
	{
		file1 >> buf1;
		file2 >> buf2;
		if (buf1 != buf2)
			return false;
	}
	return true;
}
