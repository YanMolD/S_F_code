#pragma once
#include "Tree.h"

using namespace std;

void coding(ifstream& input_file, Tree_of_codes* The_tree, ofstream& codes)
{
	char buf;
	while (!input_file.eof())
	{
		input_file.get(buf);
		for (int i = 0; i <= The_tree->Get_size(); i++)
			if (The_tree->codes[i].symb == buf)
			{
				codes << The_tree->codes[i].code;
				cout << The_tree->codes[i].code;
				break;
			}
	}
	codes << endl;
	cout << endl;
}

void calculate_comression_ratio()
{
	ifstream file_input("Text_input.txt", ios::binary | ios::ate);
	ifstream file_code("Text_code.txt", ios::binary | ios::ate);
	float i, j;
	i = file_input.tellg();
	j = file_code.tellg();
	cout << "Comression ratio is " << i * 8 / j;
}