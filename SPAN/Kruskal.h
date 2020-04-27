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
	struct nodeList
	{
		node* head = nullptr;
		nodeList* next = nullptr;
	};
	nodeList* head = nullptr;
public:
	Kruskal();
	~Kruskal();

	void makeSet(char word[WORD_LENGTH]);
	nodeList* findSet(char word[WORD_LENGTH]);
	void mergeSet(node* u, node* v);
};