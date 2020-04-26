#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments provided. Example usage:\n";
		cout << "SPAN graph_file_path\n";

		return 0;
	}

	cout << "argv[0]: " << argv[0] << "\n";
	cout << "argv[1]: " << argv[1] << "\n";

	return 0;
}