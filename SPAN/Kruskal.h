#pragma once

using namespace std;

class Kruskal
{
public:
	const static unsigned int WORD_LENGTH = 2;
private:
	struct node
	{
		char word[WORD_LENGTH];
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};
	struct edge {
		char left[WORD_LENGTH];
		char right[WORD_LENGTH];
		double weight;
	};
	node* head = nullptr;
	void insertionSort(edge arr[], int n);
public:
	Kruskal();
	~Kruskal();

	void makeSet(char word[WORD_LENGTH]);
	node* findSet(char word[WORD_LENGTH]);
	void mergeSet(node* u, node* v);
	void calculateMst(char** nodeVertices, double** weights, int numberOfNodes);
};