#pragma once

#include "Edge.h"

class ShellSort {
public:
	template <typename elementType, typename function>
	static void sort(elementType* arr, unsigned int numberOfEdges, function comparison)
	{
		unsigned int distance = 1;

		while (distance < numberOfEdges) {
			distance *= 2;
		}

		distance /= 2;

		distance--;

		do
		{
			for (unsigned int i = 0; i < (numberOfEdges - distance); i++)
			{
				for (int j = i; j >= 0; j -= distance)
				{
					if (comparison(arr[j], arr[j + distance]))
					{
						break;
					}
					else
					{
						elementType temp = arr[j];
						arr[j] = arr[j + distance];
						arr[j + distance] = temp;
					}
				}
			}

			distance--;
		} while (distance > 0);
	}
	static void orderEdgeVerticesAlphabetically(edge* edgeArray, unsigned int numberOfEdges, string* nodeVertices)
	{
		for (unsigned i = 0; i < numberOfEdges; i++)
		{
			edge& currentEdge = edgeArray[i];

			if (nodeVertices[currentEdge.u] > nodeVertices[currentEdge.v])
			{
				unsigned int temp = currentEdge.u;
				currentEdge.u = currentEdge.v;
				currentEdge.v = temp;
			}
		}
	}
	static void sortEdgesAlphabetically(edge* edgeArray, unsigned int numberOfEdges)
	{
		auto alphabeticalComparison = [](edge& edge1, edge& edge2) {
			if (edge1.u == edge2.u)
			{
				return edge1.v < edge2.v;
			}
			else
			{
				return edge1.u < edge2.u;
			}
		};

		sort(edgeArray, numberOfEdges, alphabeticalComparison);
	}
};