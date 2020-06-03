#pragma once
#include "reading.h"

using namespace std;

class Tree_of_codes
{
private:
	List* symbols;
	struct Node_tree
	{
		Node* start;
		Node* end;
		string code;
		Node_tree* zero;
		Node_tree* one;
		Node_tree* parent;
		Node_tree()
		{
			code.clear();
			start = NULL;
			end = NULL;
			zero = NULL;
			one = NULL;
			parent = NULL;
		}
		Node_tree(Node* start, Node* end, Node_tree* parent, char smb)
		{
			this->start = start;
			this->end = end;
			code = parent->code + smb;
			this->parent = parent;
			zero = NULL;
			one = NULL;
		}
	};
	struct Code_mas_node
	{
		char symb;
		string code;
		void fill(char symb, string code)
		{
			this->symb = symb;
			this->code = code;
		}
	};

	Node_tree* Root;
public:
	Code_mas_node* codes;
	Tree_of_codes(List* symb)
	{
		symbols = symb;
		Root = new Node_tree();
		Root->start = symbols->Get_Root();
		Root->end = symbols->Get_Last();
		codes = new Code_mas_node[symb->size_t()];
	}
	void initialize_tree()
	{
		int amount = symbols->get_amount();
		int cur_amount = 0;
		Node* buf = Root->start;
		if (buf->amount == amount)
		{
			Root->code = "0";
			codes[0].fill(buf->symbol, Root->code);
			if (codes[0].symb == ' ')
				cout << "Gap" << "- " << codes[0].code << endl;
			else
				if (codes[0].symb == '\n')
					cout << "Line break" << "- " << codes[0].code << endl;
				else
					cout << codes[0].symb << "- " << codes[0].code << endl;
			return;
		}
		while (buf)
		{
			cur_amount += buf->amount;
			if (cur_amount > amount / 2)
			{
				if (cur_amount - amount / 2 < -(cur_amount - buf->amount) + amount / 2)
				{
					Root->zero = new Node_tree(Root->start, buf, Root, '0');
					initialize_tree_reccont(Root->start, buf, cur_amount, Root->zero);
					Root->one = new Node_tree(buf->next, Root->end, Root, '1');
					initialize_tree_reccont(buf->next, Root->end, amount - cur_amount, Root->one);
				}
				else
				{
					Root->zero = new Node_tree(Root->start, buf->prev, Root, '0');
					initialize_tree_reccont(Root->start, buf->prev, cur_amount - buf->amount, Root->zero);
					Root->one = new Node_tree(buf, Root->end, Root, '1');
					initialize_tree_reccont(buf, Root->end, amount - (cur_amount - buf->amount), Root->one);
				}
				break;
			}
			buf = buf->next;
		}
	}
	void initialize_tree_reccont(Node* start, Node* end, int amount, Node_tree* cur_node)
	{
		if (start->next == end)
		{
			cur_node->zero = new Node_tree(start, start, cur_node, '0');
			initialize_tree_reccont(start, start, start->amount, cur_node->zero);
			cur_node->one = new Node_tree(end, end, cur_node, '1');
			initialize_tree_reccont(end, end, end->amount, cur_node->one);
			return;
		}
		int cur_amount = 0;
		Node* buf = start;
		if ((buf->amount == amount) || (start == end))
		{
			int i = 0;
			while (buf)
			{
				if (buf->prev)
					i++;
				buf = buf->prev;
			}
			codes[i].fill(start->symbol, cur_node->code);
			if (codes[i].symb == ' ')
				cout << "Gap" << "- " << codes[i].code << endl;
			else
				if (codes[i].symb == '\n')
					cout << "Line break" << "- " << codes[i].code << endl;
				else
					cout << codes[i].symb << "- " << codes[i].code << endl;
			return;
		}
		while (buf)
		{
			cur_amount += buf->amount;
			if (cur_amount > amount / 2)
			{
				if (buf == start)
					buf = buf->next;
				if (cur_amount - amount / 2 < -(cur_amount - buf->amount) + amount / 2)
				{
					cur_node->zero = new Node_tree(start, buf, cur_node, '0');
					initialize_tree_reccont(start, buf, cur_amount, cur_node->zero);
					cur_node->one = new Node_tree(buf->next, end, cur_node, '1');
					initialize_tree_reccont(buf->next, end, amount - cur_amount, cur_node->one);
				}
				else
				{
					cur_node->zero = new Node_tree(start, buf->prev, cur_node, '0');
					initialize_tree_reccont(start, buf->prev, cur_amount - buf->amount, cur_node->zero);
					cur_node->one = new Node_tree(buf, end, cur_node, '1');
					initialize_tree_reccont(buf, end, amount - (cur_amount - buf->amount), cur_node->one);
				}
				break;
			}
			buf = buf->next;
		}
	}
	void decode_file(ifstream& file)
	{
		file.seekg(0);
		int i = 0;
		string result;
		char buf_symb = NULL;
		int index = 0;
		while (!file.eof())
		{
			if (i == codes[index].code.size())
			{
				result += codes[index].symb;
				index = 0;
				i = 0;
			}
			file >> buf_symb;

			if (buf_symb == '\0')
				break;
			while (buf_symb != codes[index].code[i])
				index++;
			i++;
		}
		ofstream output_file("Text_output.txt");
		output_file.clear();
		result.pop_back();
		output_file << result;
		cout << result;
	}
	int Get_size()
	{
		return symbols->size_t();
	}
};