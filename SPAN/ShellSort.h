//==============================================================================================
// ShellSort.h
//
// This header file implements the shell sort algorithm, used to sort edge arrays by their weight,
// as well as the alphabetical representation of their edge vertices. It also includes a convenience
// method to flip edge vertices so that the vertex that is earlier in the alphabet will always be
// the edge's u vertex. The implementation resides in this header instead of a .cpp file due to
// template functions requiring their implementation to be inside of one file.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       May 4, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.
#pragma once

#include "Edge.h"

class ShellSort {
private:
	template <typename function>
	static void sort(edge* edgeArray, unsigned int numberOfEdges, function comparison)
	{
		// This method sorts the given edge array, sized numberOfEdges items, using
		// the comparison function given. The comparison function receives two edge references,
		// edge1 and edge2, and is expected to return true if edge1 should appear before edge2
		// in the array.
		//
		// Because shell sort attempts to compare and swap items that are relatively far apart,
		// we need to calculate our initial distance between items. This distance, as defined
		// by Hibbard's sequence, is 1 less than the largest power of 2 less than the number of
		// edges.
		// We start with a distance of one, as 2^0 is 1.
		unsigned int distance = 1;

		while (distance < numberOfEdges) { // While our distance is less than the number of edges,
			// we multiply our distance by two, increasing
			// our distance to the next power of two.
			distance *= 2;
		}

		// Since the distance should be the largest power of two LESS than
		// the number of edges, we divide by two to get back to that power.
		distance /= 2;

		distance--; // Finally, we decrement our distance to properly follow Hibbard's sequence.

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