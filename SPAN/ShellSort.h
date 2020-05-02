#pragma once

#include "Edge.h"

class ShellSort {
private:
	template <typename function>
	static void sort(edge* edgeArray, unsigned int numberOfEdges, function comparison)
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
					if (comparison(edgeArray[j], edgeArray[j + distance]))
					{
						break;
					}
					else
					{
						edge temp = edgeArray[j];
						edgeArray[j] = edgeArray[j + distance];
						edgeArray[j + distance] = temp;
					}
				}
			}

			distance--;
		} while (distance > 0);
	}
public:
	static void sortEdgesByWeight(edge* edgeArray, unsigned int numberOfEdges)
	{
		ShellSort::sort(edgeArray, numberOfEdges, [](edge& edge1, edge& edge2) {return edge1.weight < edge2.weight; });
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