#include <fstream>
#include <iostream>
#include "Kruskal.h"

using namespace std;

void parseGraphFile(const string& file_path)
{
	ifstream inputStream;

	inputStream.open(file_path);

	if (inputStream.fail())
	{
		cout << "Unable to open graph data file path.\n";

		return;
	}

	unsigned int numberOfNodes;

	inputStream >> numberOfNodes;

	cout << "Number of Nodes: " << numberOfNodes << "\n";

	char** nodeVertices = new char* [numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		nodeVertices[i] = new char[numberOfNodes];

		inputStream >> nodeVertices[i];
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		cout << "Node Name: " << nodeVertices[i] << "\n";
	}

	double** weights = new double* [numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		weights[i] = new double[numberOfNodes];
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		for (int j = 0; j < numberOfNodes; j++)
		{
			inputStream >> weights[i][j];
		}
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		for (int j = 0; j < numberOfNodes; j++)
		{
			cout << weights[i][j] << " ";
		}

		cout << "\n";
	}

	Kruskal kruskal;

	kruskal.calculateMst(nodeVertices, weights, numberOfNodes);

	// Deletion of node vertices array
	for (int i = 0; i < numberOfNodes; i++)
	{
		delete[] nodeVertices[i];
	}
	delete[] nodeVertices;

	// Deletion of weights matrix
	for (int i = 0; i < numberOfNodes; i++)
	{
		delete[] weights[i];
	}

	delete[] weights;

	inputStream.close();
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments provided. Example usage:\n";
		cout << "SPAN graph_file_path\n";

		return 0;
	}

	parseGraphFile(argv[1]);

	return 0;
}