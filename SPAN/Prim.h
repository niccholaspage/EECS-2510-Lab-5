#pragma once
#include <string>

using namespace std;

class Prim {
private:
	struct node
	{
		string word;
		double weight;
		string predecessor;
	};

	int extractMinNodeIndex();
	unsigned int parent(unsigned int index);
	unsigned int left(unsigned int index);
	unsigned int right(unsigned int index);
	void decreaseKey(unsigned int index, double key);
	void minHeapify(unsigned int index);
	int getPositionInQueue(unsigned int nodeIndex);

	unsigned int heapLength;
	unsigned int heapSize;

	node* nodes;
	unsigned int* heapArray;
public:
	Prim();
	~Prim();
	void calculateMst(string* nodeVertices, double** weights, int numberOfNodes);
};