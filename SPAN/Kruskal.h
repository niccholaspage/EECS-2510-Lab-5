#pragma once
#include <string>

using namespace std;

class Kruskal
{
private:
	struct node
	{
		string word;
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};
	node* head = nullptr;
public:
	Kruskal();
	~Kruskal();

	void makeSet(const string& word);
	node* findSet(const string& word);
	void mergeSet(node* u, node* v);
	void calculateMst(string* nodeVertices, double** weights, int numberOfNodes);
};