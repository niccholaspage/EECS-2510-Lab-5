#pragma once

using namespace std;

class Kruskal
{
private:
	static const unsigned int WORD_LENGTH = 2;
	struct node
	{
		char word[WORD_LENGTH];
		node* next = nullptr;
	};
	struct nodeListNode
	{
		node* node = nullptr;
		nodeListNode* next = nullptr;
	};
	nodeListNode* head = nullptr;
public:
	Kruskal();
	~Kruskal();

	void makeSet(char word[WORD_LENGTH]);
	void findSet(char word[WORD_LENGTH]);
	void mergeSet(node* u, node* v);
};