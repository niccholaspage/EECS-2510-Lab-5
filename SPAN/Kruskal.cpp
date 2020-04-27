#include "Kruskal.h"
#include <string.h>

Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{

}

void Kruskal::makeSet(char word[WORD_LENGTH])
{
	nodeList* newNodeList = new nodeList();

	node* newNode = new node();
	strcpy(newNode->word, word);

	newNodeList->head = newNode;

	if (head == nullptr)
	{
		head = newNodeList;

		return;
	}

	newNodeList->next = head;
	head->prev = newNodeList;

	head = newNodeList;
}

Kruskal::nodeList* Kruskal::findSet(char word[WORD_LENGTH])
{
	nodeList* p = head;

	while (p != nullptr)
	{
		node* q = p->head;

		while (q != nullptr)
		{
			if (strcmp(q->word, word) == 0)
			{
				return p;
			}

			q = q->next;
		}

		p = p->next;
	}

	return nullptr;
}

void Kruskal::mergeSet(nodeList* u, nodeList* v)
{
	node* p = u->head;

	while (p->next != nullptr)
	{
		p = p->next;
	}

	p->next = v->head;

	if (v->prev != nullptr)
	{
		v->prev->next = v->next;
	}

	if (v->next != nullptr)
	{
		v->next->prev = v->prev;
	}

	delete v;
}