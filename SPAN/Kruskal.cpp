#include "Kruskal.h"
#include <iostream>
#include <algorithm>
#include <vector>

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

	// Totally legal sorting
	insertionSort(edges, edgeNumber);

	for (int i = 0; i < numberOfNodes; i++)
	{
		makeSet(nodeVertices[i]);
	}

	double totalWeight = 0;

	vector<string> output;

	for (int i = 0; i < edgeNumber; i++)
	{
		edge& p = edges[i];

		node* uSet = findSet(nodeVertices[p.u]);
		node* vSet = findSet(nodeVertices[p.v]);

		if (uSet != vSet)
		{
			//cout << "Merging " << nodeVertices[p.u] << " and " << nodeVertices[p.v] << "\n";

			mergeSet(uSet, vSet);

			output.push_back(nodeVertices[p.u] + "-" + nodeVertices[p.v] + ": " + to_string((int) p.weight));

			totalWeight += p.weight;

			/*node* p = head;

			while (p != nullptr)
			{
				node* q = p;

				while (q != nullptr)
				{
					cout << q->word << " ";

					q = q->nextNeighbor;
				}

				cout << "\n";

				p = p->nextVertex;
			}*/
		}
	}

	sort(output.begin(), output.end());

	cout << "Total Weight: " << totalWeight << "\n";

	for (const string& line : output)
	{
		cout << line << "\n";
	}
}