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

	void insert(const string& word, double key);
	node* minimum();
	string extractMinWord();
	unsigned int parent(unsigned int index);
	unsigned int left(unsigned int index);
	unsigned int right(unsigned int index);
	void decreaseKey(unsigned int index, double key);
	void minHeapify(unsigned int index);
	node* getVertex(const string& word);

	unsigned int heapLength;
	unsigned int heapSize;

	node* heapArray;
public:
	Prim();
	~Prim();
	void calculateMst(string* nodeVertices, double** weights, int numberOfNodes);
};