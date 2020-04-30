#include "Prim.h"

#include <iostream>

using namespace std;

Prim::Prim()
{

}

Prim::~Prim()
{

}

int Prim::extractMinNodeIndex()
{
	if (heapSize < 1)
	{
		cout << "Error: heap underflow\n";

		return -1;
	}

	int min = heapArray[1];

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
	node* p = &nodes[heapArray[index]];

	if (key > p->weight)
	{
		cout << "New key value is greater than current key value\n";

		return;
	}

	p->weight = key;

	while (index > 1 && nodes[heapArray[parent(index)]].weight > nodes[heapArray[index]].weight)
	{
		unsigned int temp = heapArray[index];
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

	if (leftChild <= heapSize && nodes[heapArray[leftChild]].weight < nodes[heapArray[index]].weight)
	{
		smallest = leftChild;
	}
	else
	{
		smallest = index;
	}

	if (rightChild <= heapSize && nodes[heapArray[rightChild]].weight < nodes[heapArray[smallest]].weight)
	{
		smallest = rightChild;
	}

	if (smallest != index)
	{
		unsigned int temp = heapArray[index];
		heapArray[index] = heapArray[smallest];
		heapArray[smallest] = temp;
		minHeapify(smallest);
	}
}

int Prim::getPositionInQueue(unsigned int nodeIndex)
{
	for (unsigned int i = 1; i <= heapSize; i++)
	{
		if (heapArray[i] == nodeIndex)
		{
			return i;
		}
	}

	return -1;
}

void Prim::calculateMst(string* nodeVertices, double** weights, int numberOfNodes)
{
	nodes = new node[numberOfNodes];

	heapLength = numberOfNodes + 1;

	heapArray = new unsigned int[heapLength];

	heapSize = 0;

	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		node newNode;
		newNode.word = nodeVertices[i];
		newNode.weight = std::numeric_limits<double>::max();
		newNode.predecessor = "";
		nodes[i] = newNode;
		heapArray[i + 1] = i;
		heapSize++;
	}

	// I think these are functionally equivalent,
	// since setting the first node's weight to 0
	// makes its weight less than the other weights
	// of infinity, so it should be in order properly
	// heapArray[1].weight = 0;
	decreaseKey(1, 0);

	while (heapSize != 0)
	{
		int uNodeIndex = extractMinNodeIndex();

		node* u = &nodes[uNodeIndex];

		for (unsigned int i = 0; i < numberOfNodes; i++)
		{
			if (weights[uNodeIndex][i] != 0)
			{
				const string& vWord = nodeVertices[i];

				node* v = &nodes[i];

				int positionInQueue = getPositionInQueue(i);

				if (positionInQueue != -1 && weights[uNodeIndex][i] < v->weight)
				{
					double newWeight = weights[uNodeIndex][i];
					v->predecessor = u->word;
					//totalWeight += newWeight;
					//cout << uWord << "-" << v->word << ": " << newWeight << "\n";
					decreaseKey(positionInQueue, newWeight);
				}
			}
		}
	}

	double totalWeight = 0;

	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		node& p = nodes[i];

		cout << p.word << "-" << p.predecessor << ": " << p.weight << "\n";

		totalWeight += p.weight;
	}

	cout << totalWeight << "\n";

	delete[] heapArray;
}