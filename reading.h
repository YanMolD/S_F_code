#pragma once
#include "List.h"

using namespace std;

void swap_elem(Node* elem1, Node* elem2)
{
	Node* buf = elem2->prev;
	if (buf) buf->next = elem1;
	elem1->prev = buf;
	buf = elem1->next;
	elem1->next = elem2;
	if (buf) buf->prev = elem2;
	elem2->next = buf;
	elem2->prev = elem1;
}

void check_symbol(List* list_s, char symb)
{
	Node* cur = list_s->Get_Root();
	while (cur)
		if (cur->symbol == symb)
		{
			cur->amount++;
			list_s->amount_inc();
			if (cur != list_s->Get_Root())
				while ((cur->prev != NULL) && (cur->prev->amount < cur->amount))
				{
					list_s->swap_elem(cur, cur->prev);
				}
			return;
		}
		else cur = cur->next;
	list_s->push_back(symb);
}

List* read_file(ifstream& input_file)
{
	ifstream check("Text_input.txt", ios::binary | ios::ate);
	if (check.tellg() == 0)
		throw out_of_range("No symbols in file");
	List* list_s = new List();
	char buf;
	while (!input_file.eof())
	{
		input_file.get(buf);
		cout << buf;
		if (buf == -52)
			break;
		check_symbol(list_s, buf);
	}
	Node* buffer = list_s->Get_Root();
	while (buffer != NULL)
	{
		if (buffer->symbol == ' ')
			cout << "Gap " << buffer->amount << " times\n";
		else
			if (buffer->symbol == '\n')
				cout << "Line break " << buffer->amount << " times\n";
			else
				cout << buffer->symbol << ' ' << buffer->amount << " times\n";
		buffer = buffer->next;
	}
	return list_s;
}