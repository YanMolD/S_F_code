#include "coding.h"

using namespace std;

void main()
{
	ifstream input_file("Text_input.txt");
	Tree_of_codes The_tree(read_file(input_file));
	The_tree.initialize_tree();
	input_file.close();
	input_file.open("Text_input.txt");
	ofstream codes("Text_code.txt");
	codes.clear();
	coding(input_file, &The_tree, codes);
	ifstream code_file("Text_code.txt");
	The_tree.decode_file(code_file);
	calculate_comression_ratio();
}