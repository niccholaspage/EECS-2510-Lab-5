#include <fstream>
#include <iostream>

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

	inputStream.close();

	cout << "Number of Nodes: " << numberOfNodes << "\n";

	char nodeName[2];

	for (int i = 0; i < numberOfNodes; i++)
	{
		inputStream >> nodeName;

		cout << "Node Name: " << nodeName << "\n";
	}
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