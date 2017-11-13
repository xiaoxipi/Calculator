#pragma once


#include<iostream>
#include<cmath>
using namespace std;

template<class ElemType>
class Node
{
public:
	ElemType data;
	Node*  next;

	Node() {};
	Node(ElemType e, Node* n = NULL) { data = e; next = n; }

};

template<class ElemType>
class LinkStack
{
private:
	Node<ElemType> *top;
	int length;
public:
	LinkStack() { top = NULL; length = 0; }
	bool Empty() { return length == 0; }
	int Length() { return  length; }
	bool Push(ElemType &e);
	ElemType Top();
	ElemType Pop();
	void Delete();
	~LinkStack() { Delete(); }
};


template<class ElemType>
bool LinkStack<ElemType>::Push(ElemType &e)
{
	Node<ElemType>* tmp = new Node<ElemType>(e, top);
	top = tmp;
	if (top == NULL)return  false;
	length++;
	return true;
}

template<class ElemType>
ElemType LinkStack<ElemType>::Top()
{
	return top->data;
}

template<class ElemType>
ElemType LinkStack<ElemType>::Pop()
{
	if (top != NULL)
	{
		ElemType  e = top->data;
		Node<ElemType> *tmp = top;
		top = top->next;
		delete tmp;
		length--;
		return e;
	}
	return NULL;
}
template<class ElemType>
void  LinkStack<ElemType>::Delete()
{
	while (!Empty())
	{
		Pop();
	}
}