#define _CRT_SECURE_NO_WARNINGS

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
	node* newNode = new node();
	strcpy(newNode->word, word);

	if (head == nullptr)
	{
		head = newNode;

		return;
	}

	newNode->nextVertex = head;

	head = newNode;
}

Kruskal::node* Kruskal::findSet(char word[WORD_LENGTH])
{
	node* p = head;

	while (p != nullptr)
	{
		node* q = p;

		while (q != nullptr)
		{
			if (strcmp(q->word, word) == 0)
			{
				return p;
			}

			q = q->nextNeighbor;
		}

		p = p->nextVertex;
	}

	return nullptr;
}

void Kruskal::mergeSet(node* u, node* v)
{
	node* p = u;

	while (p->nextNeighbor != nullptr)
	{
		p = p->nextNeighbor;
	}

	p->nextNeighbor = v;
}

void Kruskal::calculateMst(char* nodeVertices, double** weights)
{
	node* p;


}