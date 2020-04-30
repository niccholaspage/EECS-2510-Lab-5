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

string Prim::extractMinWord()
{
	if (heapSize < 1)
	{
		cout << "Error: heap underflow\n";

		return nullptr;
	}

	node min = heapArray[1];

	heapArray[1] = heapArray[heapSize];

	heapSize--;

	minHeapify(1);

	return min.word;
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

	while (index > 1 && heapArray[parent(index)].weight > heapArray[index].weight)
	{
		node temp = heapArray[index];
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

	if (leftChild <= heapSize && heapArray[leftChild].weight < heapArray[index].weight)
	{
		smallest = leftChild;
	}
	else
	{
		smallest = index;
	}

	if (rightChild <= heapSize && heapArray[rightChild].weight < heapArray[smallest].weight)
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
	newNode.predecessor = "";

	heapArray[heapSize] = newNode;

	decreaseKey(heapSize, key);
}

Prim::node* Prim::getVertex(const string& word)
{
	for (unsigned int i = 1; i <= heapSize; i++)
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

	// I think these are functionally equivalent,
	// since setting the first node's weight to 0
	// makes its weight less than the other weights
	// of infinity, so it should be in order properly
	// heapArray[1].weight = 0;
	decreaseKey(1, 0);

	double totalWeight = 0;

	while (heapSize != 0)
	{
		string uWord = extractMinWord();

		unsigned int uRow = 0;

		for (unsigned int i = 0; i < numberOfNodes; i++)
		{
			if (nodeVertices[i] == uWord)
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
					v->predecessor = uWord;
					v->weight = weights[uRow][i];
					totalWeight += v->weight;
					cout << uWord << "-" << v->word << ": " << v->weight << "\n";
				}
			}
		}
	}

	cout << totalWeight << "\n";

	delete[] heapArray;
}