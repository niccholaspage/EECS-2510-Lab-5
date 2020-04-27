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
	nodeListNode* newNodeList = new nodeListNode();

	node* newNode = new node();
	strcpy(newNode->word, word);

	newNodeList->head = newNode;

	if (head == nullptr)
	{
		head = newNodeList;

		return;
	}

	newNodeList->next = head;

	head = newNodeList;
}

Kruskal::nodeListNode* Kruskal::findSet(char word[WORD_LENGTH])
{
	nodeListNode* p = head;

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