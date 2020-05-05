//==============================================================================================
// Kruskal.h
//
// This header file declares the fields and method needed to perform
// Kruskal's algorithm to find a minimum spanning tree of a graph.
// It utilizes a node structure, which holds a node name as well
// as the neighboring node and next vertex node, to create a linked
// list of linked lists.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       May 5, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

#pragma once
#include <string>

using namespace std;

class Kruskal
{
private:
	struct node
	{
		// A struct used to keep track of a linked
		// list of lists that Kruskal's algorithm
		// mantains to find a minimum spanning tree.
		// The next neighbor pointer can refer to a
		// node that comes after the current node,
		// and the next vertex pointer can refer to
		// the linked list that appears after the
		// given node's linked list.
		string word;
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};

	// Our linked list of linked lists is empty at
	// first, so we initialize our head to nullptr.
	node* head = nullptr;
public:
	// This method creates a set consisting of a
	// single node containing the given word,
	// and places it inside the linked list
	// of linked lists the algorithm mantains.
	void makeSet(const string& word);

	// Locates a set inside of the linked list
	// that contains a node with the given word.
	node* findSet(const string& word);

	// Merges the linked lists of each of the
	// given nodes into the given u node, and
	// fixes any links between the linked list.
	void mergeSets(node* u, node* v);

	// Calculates and prints a minimum spanning tree
	// from an undirected graph with the given node
	// names and the given weights.
	void calculateMst(string* nodeNames, unsigned int numberOfNodes, double** weights);
};