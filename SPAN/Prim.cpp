#include "Prim.h"

#include <iostream>

using namespace std;

Prim::Prim()
{

}

Prim::~Prim()
{

}

Prim::node* Prim::minimum()
{
	return &heapArray[1];
}

Prim::node* Prim::extractMin()
{
	if (heapSize < 1)
	{
		cout << "Error: heap underflow\n";

		return nullptr;
	}

	node min = heapArray[1];

	heapArray[1] = heapArray[heapSize];

	heapSize = heapSize - 1;

	minHeapify(1);

	return &min;
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
	if (key > heapArray[index].weight)
	{
		cout << "New key value is greater than current key value";

		return;
	}

	heapArray[index].weight = key;

	unsigned int parentIndex = parent(index);

	while (index > 1 && heapArray[parentIndex].weight > heapArray[index].weight)
	{
		node temp = heapArray[index];
		heapArray[index] = heapArray[parentIndex];
		heapArray[parentIndex] = temp;
		index = parent(index);
	}
}

void Prim::minHeapify(unsigned int index)
{
	unsigned int leftChild = left(index);
	unsigned int rightChild = right(index);
	unsigned int smallest;

	if (leftChild < heapSize && heapArray[leftChild].weight < heapArray[index].weight)
	{
		smallest = leftChild;
	}
	else
	{
		smallest = index;
	}

	if (rightChild < heapSize && heapArray[rightChild].weight < heapArray[smallest].weight)
	{
		smallest = rightChild;
	}

	if (smallest != index)
	{
		node temp = heapArray[index];
		heapArray[index] = heapArray[smallest];
		heapArray[smallest] = temp;
		minHeapify(smallest);
	}
}

void Prim::insert(const string& word, double key)
{
	heapSize++;

	node newNode;

	newNode.word = word;
	newNode.weight = std::numeric_limits<double>::max(); // TODO: probably no good.
	newNode.predecessor = nullptr;

	heapArray[heapSize] = newNode;

	decreaseKey(heapSize, key);
}

Prim::node* Prim::getVertex(const string& word)
{
	for (unsigned int i = 0; i < heapSize; i++)
	{
		if (heapArray[i].word == word)
		{
			return &heapArray[i];
		}
	}

	return nullptr;
}

void Prim::calculateMst(string* nodeVertices, double** weights, int numberOfNodes)
{
	heapLength = numberOfNodes + 1;

	heapArray = new node[heapLength];

	heapSize = 0;

	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		insert(nodeVertices[i], std::numeric_limits<double>::max());
	}

	heapArray[1].weight = 0;

	while (heapSize != 0)
	{
		node* u = extractMin();

		unsigned int uRow = 0;

		for (unsigned int i = 0; i < numberOfNodes; i++)
		{
			if (nodeVertices[i] == u->word)
			{
				uRow = i;

				break;
			}
		}

		for (unsigned int i = 0; i < numberOfNodes; i++)
		{
			if (weights[uRow][i] != 0)
			{
				const string& vWord = nodeVertices[i];

				node* v = getVertex(vWord);

				if (v != nullptr && weights[uRow][i] < v->weight)
				{
					v->predecessor = u;
					v->weight = weights[uRow][i];
				}
			}
		}
	}

	delete[] heapArray;
}