#define _CRT_SECURE_NO_WARNINGS

#include "Kruskal.h"
#include <iostream>
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

void Kruskal::insertionSort(edge* arr, int size)
{
	edge key;
	int j;
	for (int i = 1; i < size; i++) {
		key = arr[i];//take value
		j = i;
		while (j > 0 && arr[j - 1].weight > key.weight) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = key;   //insert in right place
	}
}

void Kruskal::calculateMst(char** nodeVertices, double** weights, int numberOfNodes)
{
	node* a = nullptr;

	for (int i = 0; i < numberOfNodes; i++)
	{
		makeSet(nodeVertices[i]);
	}

	edge* edges = new edge[numberOfNodes * numberOfNodes];

	int edgeNumber = 0;

	for (int i = 0; i < numberOfNodes; i++)
	{
		for (int j = 0; j < numberOfNodes; j++)
		{
			double weight = weights[i][j];

			if (weight != 0)
			{
				edge p;

				strcpy(p.left, nodeVertices[i]);
				strcpy(p.right, nodeVertices[j]);

				p.weight = weight;

				edges[edgeNumber] = p;

				edgeNumber++;
			}
		}
	}

	// Totally legal sorting
	insertionSort(edges, edgeNumber);

	for (int i = 0; i < edgeNumber; i++)
	{
		edge& p = edges[i];
		cout << "Edge (left: " << p.left << ", right: " << p.right << ", weight: " << p.weight << ")\n";
	}
}