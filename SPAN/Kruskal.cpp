#include "Kruskal.h"
#include "Edge.h"
#include "ShellSort.h"
#include <iostream>

void Kruskal::makeSet(const string& word)
{
	// This method simply creates a set consisting
	// of a single node containing the given word.
	// After the set is created, it is placed inside
	// of the linked list this algorithm mantains.
	//
	node* newNode = new node();	// We construct a new node,

	newNode->word = word;		// and store our word in it.

	if (head == nullptr)	// If we have no head,
	{
		head = newNode;		// we can just make our new node the head of the list.

		return;				// We've inserted our node, so we're done!
	}

	// Since we already have items in the linked list, we need to properly
	// link our new node to the linked list. We do this by inserting the
	// new node into the linked list at the beginning, as its simpler than
	// inserting it into the end.
	newNode->nextVertex = head; // We first set the next vertex of our new node to the old head,

	head = newNode;				// then we update our head to be the new node.
}

Kruskal::node* Kruskal::findSet(const string& word)
{
	// This method looks through all of the sets that
	// the algorithm is mantaining, and finds the linked
	// list that contains a node with the given word
	// in it.
	//
	node* p = head; // Let's start at the head of our list of linked lists.

	while (p != nullptr)	// While we still have an item to look for,
	{
		node* q = p;		// we set q to be the first item in our nested list p.

		while (q != nullptr) // While we still have another item left in our list,
		{
			if (q->word == word) // we check if q's word is the same as the given word.
			{
				return p; // If so, we found the linked list, so we just return the head of it!
			}

			q = q->nextNeighbor; // Since we didn't find the node yet, we check the element right after q.
		}

		// We weren't able to find the word in this linked list, so we proceed to the next vertex or linked list.
		p = p->nextVertex;
	}

	return nullptr; // We couldn't find any list with the given word, we return a null pointer!
}

void Kruskal::mergeSets(node* u, node* v)
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
			mergeSets(uSet, vSet);

			mergedEdges[currentEdgeNumber] = p;

			currentEdgeNumber++;

			totalWeight += p.weight;
		}
	}

	ShellSort::orderEdgeVerticesAlphabetically(mergedEdges, currentEdgeNumber, nodeVertices);

	ShellSort::sortEdgesAlphabetically(mergedEdges, currentEdgeNumber, nodeVertices);

	cout << "Kruskal:\n";

	cout << totalWeight << "\n";

	for (unsigned i = 0; i < currentEdgeNumber; i++)
	{
		edge& mergedEdge = mergedEdges[i];

		cout << nodeVertices[mergedEdge.u] << "-" + nodeVertices[mergedEdge.v] << ": " << mergedEdge.weight << "\n";
	}

	delete[] edges;
}