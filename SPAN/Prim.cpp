#include "Prim.h"

#include <iostream>

using namespace std;

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

void Prim::decreaseKey(node* x, unsigned int index, node key)
{
	if (key.weight > heapArray[index].weight)
	{
		cout << "New key value is greater than current key value";

		return;
	}

	heapArray[index] = key;

	unsigned int parentIndex = parent(index);

	while (index > 1 && heapArray[parentIndex].weight > heapArray[index].weight)
	{
		node temp = heapArray[index];
		heapArray[index] = heapArray[parentIndex];
		heapArray[parentIndex] = temp;
		index = parent(index);
	}
}