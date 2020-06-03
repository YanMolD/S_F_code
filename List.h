#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Node
{
	char symbol;
	int amount;
	Node* next;
	Node* prev;
	Node(char value)
	{
		symbol = value;
		amount = 1;
		next = NULL;
		prev = NULL;
	}
	Node(Node* value)
	{
		symbol = value->symbol;
		amount = value->amount;
		next = NULL;
		prev = NULL;
	}
};

class List
{
private:
	Node* Root;
	Node* Last;
	int amount;
public:
	List()
	{
		Root = NULL;
		Last = NULL;
		amount = 0;
	}
	List(Node* start, Node* end)
	{
		Root = new Node(start);
		Last = Root;
		Node* buf = Root;
		while (buf != end->next)
		{
			push_back(buf);
			amount += buf->amount;
			buf = buf->next;
		}
	}
	~List()
	{
		while (Root != NULL)
		{
			Node* n = Root->next;
			delete Root;
			Root = n;
		}
	}
	Node* Get_Root()
	{
		return Root;
	}
	Node* Get_Last()
	{
		return Last;
	}
	void push_back(char value)
	{
		amount++;
		if (Last != NULL)
		{
			Last->next = new Node(value);
			Last->next->prev = Last;
			Last = Last->next;
		}
		else
		{
			Last = new Node(value);
			Root = Last;
		}
	}
	void push_back(Node* value)
	{
		amount += value->amount;
		if (Last == NULL)
		{
			Last = new Node(value);
			Root = Last;
		}
		else
		{
			Last->next = new Node(value);
			Last->next->prev = Last;
			Last = Last->next;
		}
	}
	void push_front(char value)
	{
		Node* buf = new Node(value);
		buf->next = Root;
		if (Root == NULL)
			Last = buf;
		else
			Root->prev = buf;
		Root = buf;
	}
	void pop_back()
	{
		if (Last != Root)
		{
			Node* buf = Last->prev;
			delete Last;
			Last = buf;
			Last->next = NULL;
		}
		else
			clear();
	}
	void pop_front()
	{
		if (Root != Last)
		{
			Node* n = Root->next;
			delete Root;
			Root = n;
			Root->prev = NULL;
		}
		else
			clear();
	}
	void insert(char value, int number)
	{
		if (number > size_t() || (number < 0))
			throw out_of_range("Index more than size of List");
		Node* buf_list = Root;
		if (number == size_t() - 1)
		{
			push_back(value);
			return;
		}
		if (number > 0)
		{
			for (int f = 0; f < number; f++)
				buf_list = buf_list->next;
			Node* new_element = new Node(value);
			buf_list->prev->next = new_element;
			new_element->prev = buf_list->prev;
			buf_list->prev = new_element;
		}
		else
			push_front(value);
	}
	int at(int number)
	{
		if (number > size_t() || (number < 0))
			throw out_of_range("Index more than size of List");
		Node* n = Root;
		for (int f = 0; f < number; f++)
			n = n->next;
		return n->symbol;
	}
	void remove(int number)
	{
		if (number > size_t() || (number < 0))
			throw out_of_range("Index more than size of List");
		Node* n = Root;
		if (number > 0)
		{
			for (int f = 0; f < number; f++)
				n = n->next;
			if (n == Last)
			{
				pop_back();
				return;
			}
			n->prev->next = n->next;
			n->prev->next->prev = n->prev;
			delete n;
		}
		else
			pop_front();
	}
	int size_t()
	{
		int f = 0;
		Node* buf_list = Root;
		while (buf_list != NULL)
		{
			buf_list = buf_list->next;
			f++;
		}
		return f;
	}
	void print_to_console()
	{
		Node* buf_list = Root;
		while (buf_list != NULL)
		{
			cout << buf_list->symbol << ' ';
			buf_list = buf_list->next;
		}
		cout << '\n';
	}
	void clear()
	{
		while (Root != NULL)
		{
			Node* buf_list = Root->next;
			delete Root;
			Root = buf_list;
		}
		Root = NULL;
		Last = NULL;
	}
	void set(char value, int number)
	{
		if (number >= size_t() || (number < 0))
			throw out_of_range("Index more than size of List");
		Node* buf_list = Root;
		for (int f = 0; f < number; f++)
			buf_list = buf_list->next;
		buf_list->symbol = value;
	}
	bool isEmpty()
	{
		if (Root == NULL)
			return 1;
		return 0;
	}
	bool contains(char value)
	{
		Node* buf = Root;
		while (buf != NULL)
			if (buf->symbol == value)
				return true;
			else
				buf = buf->next;
		return false;
	}
	void amount_inc()
	{
		amount++;
	}
	int get_amount()
	{
		return amount;
	}
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
		if (elem1->prev == NULL)
			Root = elem1;
		if (elem2->next == NULL)
			Last = elem2;
	}
};
