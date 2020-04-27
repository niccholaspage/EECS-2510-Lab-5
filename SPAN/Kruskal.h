#pragma once

using namespace std;

class Kruskal
{
private:
	const static unsigned int WORD_LENGTH = 2;
	struct node
	{
		char word[WORD_LENGTH];
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};
	node* head = nullptr;
public:
	Kruskal();
	~Kruskal();

	void makeSet(char word[WORD_LENGTH]);
	node* findSet(char word[WORD_LENGTH]);
	void mergeSet(node* u, node* v);
	void calculateMst();
};