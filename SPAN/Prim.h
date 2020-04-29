#pragma once
#include <string>

using namespace std;

class Prim {
private:
	struct node
	{
		string word;
		double weight;
	};

	void insert(const string& word, double key);
	node* minimum();
	node* extractMin();
	unsigned int parent(unsigned int index);
	unsigned int left(unsigned int index);
	unsigned int right(unsigned int index);
	void decreaseKey(unsigned int index, double key);
	void minHeapify(unsigned int index);

	unsigned int heapLength;
	unsigned int heapSize;

	node heapArray[];
public:
	Prim();
	~Prim();
};