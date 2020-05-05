#pragma once
#include <string>
#include "Edge.h"

using namespace std;

class Prim {
private:
	edge* extractMinNode();
	unsigned int parent(unsigned int index);
	unsigned int left(unsigned int index);
	unsigned int right(unsigned int index);
	void decreaseKey(unsigned int index, double key);
	void minHeapify(unsigned int index);
	unsigned int getPositionInQueue(const edge& p);

	unsigned int heapLength;
	unsigned int heapSize;

	edge* nodes;
	edge** heapArray;
public:
	void calculateMst(string* nodeNames, unsigned int numberOfNodes, double** weights);
};