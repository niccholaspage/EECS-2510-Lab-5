#include <fstream>
#include <iostream>
#include "Kruskal.h"
#include "Prim.h"

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

	// We hold the number of nodes read from the file here.
	unsigned int numberOfNodes;

	// The first line of the file will have the number of nodes,
	// so we simply pipe it into our number of nodes variable.
	inputStream >> numberOfNodes;

	// We dynamically allocate a string array of size numberOfNodes,
	// which will store all of our node names.
	string* nodeNames = new string[numberOfNodes];

	// We loop numberOfNodes times, as that is how many
	// nodes we will have.
	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		// We now simply pipe our input stream into
		// our nodeNames array at position i,
		// which will put the node name
		// into our array at the right position.
		inputStream >> nodeNames[i];
	}

	// We need a 2D array containing our weights / adjacency
	// matrix. To do this, we create an array of double
	// pointers, with each pointer of this array pointing
	// to the first double of each row of the matrix.
	// The new keyword will then return a pointer to the
	// first pointer in our adjacency matrix, meaning
	// the item at the first row and column of the
	// matrix.
	double** weights = new double* [numberOfNodes];

	// We now need to loop through our number of nodes,
	// and initialize each row of the adjacency matrix
	// to a new double array with a size of number of nodes.
	// When this loop finishes executing, we will successfully
	// created our matrix, but have not initialized its
	// values.
	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		weights[i] = new double[numberOfNodes];
	}

	// We now loop through each row, and then
	// each column of the matrix, reading the input
	// stream for the weight, and piping it into our
	// adjacency matrix. After these two loops, our
	// adjacency matrix is complete.
	for (unsigned int i = 0; i < numberOfNodes; i++)
	{
		for (unsigned int j = 0; j < numberOfNodes; j++)
		{
			inputStream >> weights[i][j];
		}
	}

	Kruskal* kruskal = new Kruskal();

	kruskal->calculateMst(nodeNames, numberOfNodes, weights);

	delete kruskal;

	cout << "---------------------------------------------------------------\n";

	Prim* prim = new Prim();

	prim->calculateMst(nodeNames, numberOfNodes, weights);

	delete prim;

	// Deletion of node names array
	delete[] nodeNames;

	// Deletion of weights matrix
	for (unsigned int i = 0; i < numberOfNodes; i++)
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