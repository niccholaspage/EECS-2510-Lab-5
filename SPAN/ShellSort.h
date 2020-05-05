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
// Date:       May 5, 2020
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
			// In each pass of our do...while loop, we will perform swaps
			// on elements in our array, that are a certain number of spaces
			// apart, based on our current distance.
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
						// We perform a swap of edgeArray[j] and edgeArray[j + distance]

						// Assign the edge at position j of the array to a temporary variable,
						edge temp = edgeArray[j];
						// set the edge at position j in the array to the edge at j + distance in the array,
						edgeArray[j] = edgeArray[j + distance];
						// and finally, set the element at j + distance in the array to our temporary edge.
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
		// This method sorts the given edges array, with a
		// size of numberOfEdges, by the weights of the edge.
		//
		// We simply call our shell sort, passing in a lambda that returns
		// true if our first edge's weight is less than our second edge's,
		// making edge1 appear to the left of edge2 in the array.
		ShellSort::sort(edgeArray, numberOfEdges, [](edge& edge1, edge& edge2) {return edge1.weight < edge2.weight; });
	}
	static void orderEdgeVerticesAlphabetically(edge* edgeArray, unsigned int numberOfEdges, string* nodeVertices)
	{
		// This method simply orders the two vertices in each
		// edge of the given edges array, with a size of
		// numberOfEdges. If an edge's u node is alphabetically
		// before its v node, the u and v node will be swapped.
		for (unsigned i = 0; i < numberOfEdges; i++) // Loop through every edge in the array,
		{
			edge& currentEdge = edgeArray[i]; // Get a reference to the edge.

			// If the alphabetical representation of u is greater than v,
			if (nodeVertices[currentEdge.u] > nodeVertices[currentEdge.v])
			{
				// We perform a swap!
				unsigned int temp = currentEdge.u;	// Assign u to a temporary variable,
				currentEdge.u = currentEdge.v;		// set u to v,
				currentEdge.v = temp;				// and set v to our temporary variable, completing the swap.
			}
		}
	}
	static void sortEdgesAlphabetically(edge* edgeArray, unsigned int numberOfEdges, string* nodeVertices)
	{
		// This method sorts the given edges array, with a
		// size of numberOfEdges, by using string comparisons
		// on the name of the node vertices. Since our edge struct
		// does not contain the string representation of the node,
		// an array of node vertice strings needs to be passed.
		//
		// We define our alphabetical comparison lambda here
		// just so the code below looks cleaner.
		auto alphabeticalComparison = [&](edge& edge1, edge& edge2) {
			if (edge1.u == edge2.u) // If edge 1 and 2 have the same u node,
			{
				return nodeVertices[edge1.v] < nodeVertices[edge2.v]; // we check the v nodes.
			}
			else // otherwise,
			{
				return nodeVertices[edge1.u] < nodeVertices[edge2.u]; // we check the u nodes.
			}
		};

		// We simply call our shell sort, passing in a lambda that returns
		// true if our first edge's u node string is less than our second
		// edge's, making edge1 appear to the left of edge2 in the array.
		// If our first and second edge both have the same u node,
		// we simply sort based off of the second vertice, v.
		sort(edgeArray, numberOfEdges, alphabeticalComparison);
	}
};