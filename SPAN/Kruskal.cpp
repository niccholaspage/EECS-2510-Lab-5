#include "Kruskal.h"
#include "Edge.h"
#include "ShellSort.h"
#include <iostream>

Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{

}

void Kruskal::makeSet(const string& word)
{
	node* newNode = new node();

	newNode->word = word;

	if (head == nullptr)
	{
		head = newNode;

		return;
	}

	newNode->nextVertex = head;

	head = newNode;
}

Kruskal::node* Kruskal::findSet(const string& word)
{
	node* p = head;

	while (p != nullptr)
	{
		node* q = p;

		while (q != nullptr)
		{
			if (q->word == word)
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

	node* q = head;

	while (q->nextVertex != nullptr)
	{
		if (q->nextVertex == v)
		{
			q->nextVertex = v->nextVertex;

			break;
		}

		q = q->nextVertex;
	}

	if (head == v)
	{
		head = v->nextVertex;
	}

	v->nextVertex = nullptr;
}

void Kruskal::calculateMst(string* nodeVertices, double** weights, int numberOfNodes)
{
	node* a = nullptr;

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

				p.u = i;
				p.v = j;

				p.weight = weight;

				edges[edgeNumber] = p;

				edgeNumber++;
			}
		}
	}

	ShellSort::sortEdgesByWeight(edges, edgeNumber);

	for (int i = 0; i < numberOfNodes; i++)
	{
		makeSet(nodeVertices[i]);
	}

	double totalWeight = 0;

	edge* mergedEdges = new edge[numberOfNodes - 1];

	unsigned int currentEdgeNumber = 0;

	for (int i = 0; i < edgeNumber; i++)
	{
		edge& p = edges[i];

		node* uSet = findSet(nodeVertices[p.u]);
		node* vSet = findSet(nodeVertices[p.v]);

		if (uSet != vSet)
		{
			mergeSet(uSet, vSet);

			mergedEdges[currentEdgeNumber] = p;

			currentEdgeNumber++;

			totalWeight += p.weight;
		}
	}

	ShellSort::orderEdgeVerticesAlphabetically(mergedEdges, currentEdgeNumber, nodeVertices);

	ShellSort::sortEdgesAlphabetically(mergedEdges, currentEdgeNumber);

	cout << totalWeight << "\n";

	for (unsigned i = 0; i < currentEdgeNumber; i++)
	{
		edge& mergedEdge = mergedEdges[i];

		cout << nodeVertices[mergedEdge.u] << "-" + nodeVertices[mergedEdge.v] << ": " << mergedEdge.weight << "\n";
	}

	delete[] edges;
}