#pragma once
class Prim {
private:
	const static unsigned int WORD_LENGTH = 2;
	struct node
	{
		char word[WORD_LENGTH];
		double weight;
	};

	unsigned int heapLength;
	unsigned int heapSize;

	node* array[100]; // TODO: Somehow figure out variable sizing.
public:
	Prim();
	~Prim();

	void insert(char word[WORD_LENGTH], double weight);
	node* maximum();
	node* extractMax();
	void increaseKey(node* x, int k);
	void maxHeapify();
};