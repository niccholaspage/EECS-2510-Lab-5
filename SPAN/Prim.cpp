#include "Prim.h"

#include <iostream>

#include "ShellSort.h"

using namespace std;

Prim::Prim()
{

}

Prim::~Prim()
{

}

edge* Prim::extractMinNode()
{
	if (heapSize < 1)
	{
		cout << "Error: heap underflow\n";

		return nullptr;
	}

	edge* min = heapArray[1];

	heapArray[1] = heapArray[heapSize];

	heapSize--;

	minHeapify(1);

	return min;
}

unsigned Prim::left(unsigned int index)
{
	return 2 * index;
}

unsigned int Prim::right(unsigned int index)
{
	return 2 * index + 1;
}

unsigned int Prim::parent(unsigned int index)
{
	return index / 2;
}

void Prim::decreaseKey(unsigned int index, double key)
{
	edge* p = heapArray[index];

	if (key > p->weight)
	{
		cout << "New key value is greater than current key value\n";

		return;
	}

	p->weight = key;

	while (index > 1 && heapArray[parent(index)]->weight > heapArray[index]->weight)
	{
		edge* temp = heapArray[index];
		heapArray[index] = heapArray[parent(index)];
		heapArray[parent(index)] = temp;
		index = parent(index);
	}
}

void Prim::minHeapify(unsigned int index)
{
	unsigned int leftChild = left(index);
	unsigned int rightChild = right(index);
	unsigned int smallest;

	if (leftChild <= heapSize && heapArray[leftChild]->weight < heapArray[index]->weight)
	{
		smallest = leftChild;
	}
	else
	{
		smallest = index;
	}

	if (rightChild <= heapSize && heapArray[rightChild]->weight < heapArray[smallest]->weight)
	{
		smallest = rightChild;
	}

	if (smallest != index)
	{
		edge* temp = heapArray[index];
		heapArray[index] = heapArray[smallest];
		heapArray[smallest] = temp;
		minHeapify(smallest);
	}
}

unsigned int Prim::getPositionInQueue(const edge& p)
{
	for (unsigned int i = 1; i <= heapSize; i++)
	{
		if (heapArray[i] == &p)
		{
			return i;
		}
	}

	return 0;
}

void Prim::calculateMst(string* nodeVertices, double** weights, int numberOfNodes)
{
	nodes = new edge[numberOfNodes];

	heapLength = numberOfNodes + 1;

	heapArray = new edge * [heapLength];

	heapSize = 0;

	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		edge newNode;
		newNode.u = i;
		newNode.weight = std::numeric_limits<double>::max();
		newNode.v = i;
		nodes[i] = newNode;
		heapArray[i + 1] = &nodes[i];
		heapSize++;
	}

	decreaseKey(1, 0);

	while (heapSize != 0)
	{
		edge* u = extractMinNode();

		unsigned int uNodeIndex = u - &nodes[0];

		for (unsigned int i = 0; i < numberOfNodes; i++)
		{
			if (weights[uNodeIndex][i] != 0)
			{
				const string& vWord = nodeVertices[i];

				edge& v = nodes[i];

				unsigned int positionInQueue = getPositionInQueue(v);

				if (positionInQueue != 0 && weights[uNodeIndex][i] < v.weight)
				{
					double newWeight = weights[uNodeIndex][i];
					v.v = uNodeIndex;
					decreaseKey(positionInQueue, newWeight);
				}
			}
		}
	}

	ShellSort::orderEdgeVerticesAlphabetically(nodes, numberOfNodes, nodeVertices);

	ShellSort::sortEdgesAlphabetically(nodes, numberOfNodes);

	double totalWeight = 0;

	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		const edge& p = nodes[i];

		if (p.v != p.u)
		{
			totalWeight += p.weight;
		}
	}

	cout << totalWeight << "\n";

	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		const edge& p = nodes[i];

		if (p.v != p.u)
		{
			cout << nodeVertices[p.u] << "-" << nodeVertices[p.v] << ": " << p.weight << "\n";
		}
	}

	delete[] nodes;

	delete[] heapArray;
}